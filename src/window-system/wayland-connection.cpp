/**
 * Copyright 2026 The Touchégg contributors
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#include "window-system/wayland-connection.h"

#include <poll.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "protocols/fake-input-client-protocol.h"
#include "protocols/wlr-layer-shell-unstable-v1-client-protocol.h"
#include "utils/logger.h"

namespace {
// org_kde_kwin_fake_input v6 added keyboard_keysym
constexpr uint32_t FAKE_INPUT_KEYSYM_VERSION = 6;
constexpr uint32_t FAKE_INPUT_MAX_VERSION = 6;
constexpr uint32_t OUTPUT_MAX_VERSION = 4;
constexpr uint32_t COMPOSITOR_MAX_VERSION = 4;
constexpr uint32_t LAYER_SHELL_MAX_VERSION = 4;

void onOutputGeometry(void *data, wl_output * /*output*/, int32_t /*x*/,
                      int32_t /*y*/, int32_t /*physicalWidth*/,
                      int32_t /*physicalHeight*/, int32_t /*subpixel*/,
                      const char * /*make*/, const char * /*model*/,
                      int32_t transform) {
  static_cast<WaylandConnection::Output *>(data)->transform = transform;
}

void onOutputMode(void * /*data*/, wl_output * /*output*/, uint32_t /*flags*/,
                  int32_t /*width*/, int32_t /*height*/, int32_t /*refresh*/) {}

void onOutputDone(void * /*data*/, wl_output * /*output*/) {}

void onOutputScale(void *data, wl_output * /*output*/, int32_t factor) {
  static_cast<WaylandConnection::Output *>(data)->scale = std::max(1, factor);
}

void onOutputName(void *data, wl_output * /*output*/, const char *name) {
  static_cast<WaylandConnection::Output *>(data)->name = name;
}

void onOutputDescription(void * /*data*/, wl_output * /*output*/,
                         const char * /*description*/) {}

const wl_output_listener OUTPUT_LISTENER = {
    onOutputGeometry, onOutputMode, onOutputDone,
    onOutputScale,    onOutputName, onOutputDescription,
};
}  // namespace

WaylandConnection::WaylandConnection() {
  this->display = wl_display_connect(nullptr);
  if (this->display == nullptr) {
    throw std::runtime_error("Error connecting to the Wayland compositor");
  }

  static const wl_registry_listener registryListener = {
      WaylandConnection::onGlobal, WaylandConnection::onGlobalRemove};
  this->registry = wl_display_get_registry(this->display);
  wl_registry_add_listener(this->registry, &registryListener, this);

  // First roundtrip to get the globals, second one to get the output details
  wl_display_roundtrip(this->display);
  wl_display_roundtrip(this->display);

  if (this->fakeInput == nullptr) {
    tlg::error
        << "The compositor doesn't allow Touchégg to emulate keyboard and "
           "mouse events (org_kde_kwin_fake_input). Keyboard shortcuts and "
           "mouse clicks will not work. Make sure a .desktop file with "
           "\"X-KDE-Wayland-Interfaces=org_kde_kwin_fake_input\" and "
           "\"Exec=<path to the touchegg executable>\" is installed"
        << std::endl;
  } else if (this->fakeInputVersion < FAKE_INPUT_KEYSYM_VERSION) {
    tlg::error << "Your KWin version is too old to emulate keyboard shortcuts "
                  "(org_kde_kwin_fake_input v"
               << FAKE_INPUT_KEYSYM_VERSION << " is required)" << std::endl;
  }

  if (this->layerShell == nullptr) {
    tlg::info << "The compositor doesn't support wlr_layer_shell, animations "
                 "will not be displayed"
              << std::endl;
  }
}

WaylandConnection::~WaylandConnection() {
  for (auto &output : this->outputs) {
    wl_output_destroy(output->output);
  }
  this->outputs.clear();

  if (this->fakeInput != nullptr) {
    org_kde_kwin_fake_input_destroy(this->fakeInput);
  }
  if (this->layerShell != nullptr) {
    zwlr_layer_shell_v1_destroy(this->layerShell);
  }
  if (this->shm != nullptr) {
    wl_shm_destroy(this->shm);
  }
  if (this->compositor != nullptr) {
    wl_compositor_destroy(this->compositor);
  }
  if (this->registry != nullptr) {
    wl_registry_destroy(this->registry);
  }
  wl_display_disconnect(this->display);
}

std::string WaylandConnection::getDisplayName() const {
  const char *name = std::getenv("WAYLAND_DISPLAY");
  return (name != nullptr) ? std::string{name} : std::string{"wayland-0"};
}

bool WaylandConnection::canSendInput() const {
  return this->fakeInput != nullptr &&
         this->fakeInputVersion >= FAKE_INPUT_KEYSYM_VERSION;
}

void WaylandConnection::sendKeysym(uint32_t keysym, bool isPress) {
  if (!this->canSendInput()) {
    return;
  }

  org_kde_kwin_fake_input_keyboard_keysym(
      this->fakeInput, keysym,
      isPress ? WL_KEYBOARD_KEY_STATE_PRESSED : WL_KEYBOARD_KEY_STATE_RELEASED);
  wl_display_flush(this->display);
}

void WaylandConnection::sendButton(uint32_t button, bool isPress) {
  if (this->fakeInput == nullptr) {
    return;
  }

  org_kde_kwin_fake_input_button(this->fakeInput, button,
                                 isPress ? WL_POINTER_BUTTON_STATE_PRESSED
                                         : WL_POINTER_BUTTON_STATE_RELEASED);
  wl_display_flush(this->display);
}

const WaylandConnection::Output *WaylandConnection::findOutput(
    const std::string &name) const {
  for (const auto &output : this->outputs) {
    if (output->name == name) {
      return output.get();
    }
  }
  return nullptr;
}

void WaylandConnection::dispatchPending() {
  while (wl_display_prepare_read(this->display) != 0) {
    wl_display_dispatch_pending(this->display);
  }
  wl_display_flush(this->display);

  pollfd fd = {wl_display_get_fd(this->display), POLLIN, 0};
  if (poll(&fd, 1, 0) > 0) {
    wl_display_read_events(this->display);
  } else {
    wl_display_cancel_read(this->display);
  }
  wl_display_dispatch_pending(this->display);
}

void WaylandConnection::roundtrip() { wl_display_roundtrip(this->display); }

void WaylandConnection::onGlobal(void *data, wl_registry *registry,
                                 uint32_t name, const char *interface,
                                 uint32_t version) {
  auto *self = static_cast<WaylandConnection *>(data);

  if (std::strcmp(interface, wl_compositor_interface.name) == 0) {
    self->compositor = static_cast<wl_compositor *>(
        wl_registry_bind(registry, name, &wl_compositor_interface,
                         std::min(version, COMPOSITOR_MAX_VERSION)));
  } else if (std::strcmp(interface, wl_shm_interface.name) == 0) {
    self->shm = static_cast<wl_shm *>(
        wl_registry_bind(registry, name, &wl_shm_interface, 1));
  } else if (std::strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
    self->layerShell = static_cast<zwlr_layer_shell_v1 *>(
        wl_registry_bind(registry, name, &zwlr_layer_shell_v1_interface,
                         std::min(version, LAYER_SHELL_MAX_VERSION)));
  } else if (std::strcmp(interface, org_kde_kwin_fake_input_interface.name) ==
             0) {
    self->fakeInputVersion = std::min(version, FAKE_INPUT_MAX_VERSION);
    self->fakeInput = static_cast<org_kde_kwin_fake_input *>(
        wl_registry_bind(registry, name, &org_kde_kwin_fake_input_interface,
                         self->fakeInputVersion));
    org_kde_kwin_fake_input_authenticate(self->fakeInput, "Touchégg",
                                         "Execute your gestures actions");
  } else if (std::strcmp(interface, wl_output_interface.name) == 0) {
    auto output = std::make_unique<Output>();
    output->globalName = name;
    output->output = static_cast<wl_output *>(
        wl_registry_bind(registry, name, &wl_output_interface,
                         std::min(version, OUTPUT_MAX_VERSION)));
    wl_output_add_listener(output->output, &OUTPUT_LISTENER, output.get());
    self->outputs.push_back(std::move(output));
  }
}

void WaylandConnection::onGlobalRemove(void *data, wl_registry * /*registry*/,
                                       uint32_t name) {
  auto *self = static_cast<WaylandConnection *>(data);
  auto it = std::find_if(
      self->outputs.begin(), self->outputs.end(),
      [name](const auto &output) { return output->globalName == name; });

  if (it != self->outputs.end()) {
    wl_output_destroy((*it)->output);
    self->outputs.erase(it);
  }
}

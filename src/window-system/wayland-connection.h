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
#ifndef WINDOW_SYSTEM_WAYLAND_CONNECTION_H_
#define WINDOW_SYSTEM_WAYLAND_CONNECTION_H_

#include <wayland-client.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

struct org_kde_kwin_fake_input;
struct zwlr_layer_shell_v1;

/**
 * Connection to the Wayland compositor (KWin).
 *
 * - org_kde_kwin_fake_input is used to emulate keyboard and mouse events. KWin
 *   only exposes it to programs listed in a .desktop file with
 *   "X-KDE-Wayland-Interfaces=org_kde_kwin_fake_input".
 * - wlr_layer_shell is used to draw the animations on top of the windows.
 */
class WaylandConnection {
 public:
  struct Output {
    wl_output *output = nullptr;
    uint32_t globalName = 0;
    std::string name;
    int32_t scale = 1;
    int32_t transform = WL_OUTPUT_TRANSFORM_NORMAL;
  };

  WaylandConnection();
  ~WaylandConnection();

  WaylandConnection(const WaylandConnection &) = delete;
  WaylandConnection &operator=(const WaylandConnection &) = delete;

  /**
   * @returns The name of the Wayland display, for example "wayland-0".
   */
  std::string getDisplayName() const;

  wl_display *getDisplay() const { return this->display; }
  wl_compositor *getCompositor() const { return this->compositor; }
  wl_shm *getShm() const { return this->shm; }
  zwlr_layer_shell_v1 *getLayerShell() const { return this->layerShell; }

  /**
   * @returns If the compositor allows us to emulate input events.
   */
  bool canSendInput() const;

  /**
   * Emulate a key press/release. The compositor translates the keysym to a
   * keycode using the current keyboard layout.
   */
  void sendKeysym(uint32_t keysym, bool isPress);

  /**
   * Emulate a mouse button press/release.
   * @param button Linux input event code, for example BTN_LEFT.
   */
  void sendButton(uint32_t button, bool isPress);

  /**
   * @returns The output with the given name (for example "eDP-1") or nullptr.
   */
  const Output *findOutput(const std::string &name) const;

  /**
   * Send pending requests and dispatch the events received, without blocking.
   */
  void dispatchPending();

  /**
   * Block until the compositor processed all the requests.
   */
  void roundtrip();

 private:
  wl_display *display = nullptr;
  wl_registry *registry = nullptr;
  wl_compositor *compositor = nullptr;
  wl_shm *shm = nullptr;
  zwlr_layer_shell_v1 *layerShell = nullptr;
  org_kde_kwin_fake_input *fakeInput = nullptr;
  uint32_t fakeInputVersion = 0;
  std::vector<std::unique_ptr<Output>> outputs;

  static void onGlobal(void *data, wl_registry *registry, uint32_t name,
                       const char *interface, uint32_t version);
  static void onGlobalRemove(void *data, wl_registry *registry, uint32_t name);
};

#endif  // WINDOW_SYSTEM_WAYLAND_CONNECTION_H_

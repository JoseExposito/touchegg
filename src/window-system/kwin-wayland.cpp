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
#include "window-system/kwin-wayland.h"

#include <gio/gio.h>
#include <linux/input-event-codes.h>
#include <xkbcommon/xkbcommon.h>

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "utils/logger.h"
#include "window-system/wayland-cairo-surface.h"

namespace {
// Window under the cursor, mirroring the X11 implementation:
// - "Normal" windows are the only non system windows
// - KWin::MaximizeFull == 3
constexpr auto SCRIPT_WINDOW_UNDER_CURSOR = R"JS(
  const windows = workspace.windowAt(workspace.cursorPos, 1);
  if (windows.length === 0) {
    return { valid: false };
  }
  const window = windows[0];
  const geometry = window.frameGeometry;
  const icon = window.iconGeometry;
  return {
    valid: true,
    internalId: window.internalId.toString(),
    resourceClass: window.resourceClass,
    desktopFileName: window.desktopFileName,
    x: geometry.x, y: geometry.y,
    width: geometry.width, height: geometry.height,
    iconX: icon.x, iconY: icon.y,
    iconWidth: icon.width, iconHeight: icon.height,
    maximized: window.maximizeMode === 3,
    fullscreen: window.fullScreen,
    system: !window.normalWindow,
  };
)JS";

constexpr auto SCRIPT_OUTPUT_UNDER_CURSOR = R"JS(
  const output = workspace.screenAt(workspace.cursorPos);
  if (!output) {
    return {};
  }
  const geometry = output.geometry;
  const workarea =
      workspace.clientArea(KWin.MaximizeArea, output, workspace.currentDesktop);
  return {
    name: output.name,
    x: geometry.x, y: geometry.y,
    width: geometry.width, height: geometry.height,
    workareaX: workarea.x, workareaY: workarea.y,
    workareaWidth: workarea.width, workareaHeight: workarea.height,
  };
)JS";

// Same logic as X11::changeDesktop and X11::destinationDesktop
constexpr auto SCRIPT_CHANGE_DESKTOP = R"JS(
  const desktops = workspace.desktops;
  const total = desktops.length;
  const columns = Math.max(1, workspace.desktopGridWidth);
  const currentId = workspace.currentDesktop.id;
  let current = 0;
  for (let i = 0; i < total; i++) {
    if (desktops[i].id === currentId) {
      current = i;
    }
  }

  let to = -1;
  switch (DIRECTION) {
    case "UP":
      if (current >= columns) {
        to = current - columns;
      }
      break;
    case "DOWN":
      if (current < total - columns) {
        to = current + columns;
      }
      break;
    case "LEFT":
      if (current > Math.floor(current / columns) * columns) {
        to = current - 1;
      }
      break;
    case "RIGHT":
      if (current < Math.min(total - 1,
                             Math.floor(current / columns) * columns +
                                 columns - 1)) {
        to = current + 1;
      }
      break;
    case "NEXT":
      to = CYCLIC ? (current + 1) % total : Math.min(total - 1, current + 1);
      break;
    default:
      to = CYCLIC ? ((current - 1) % total + total) % total
                  : Math.max(0, current - 1);
      break;
  }

  if (to >= 0 && to < total && to !== current) {
    workspace.currentDesktop = desktops[to];
  }
)JS";

std::string actionDirectionToJs(ActionDirection direction) {
  switch (direction) {
    case ActionDirection::UP:
      return "UP";
    case ActionDirection::DOWN:
      return "DOWN";
    case ActionDirection::LEFT:
      return "LEFT";
    case ActionDirection::RIGHT:
      return "RIGHT";
    case ActionDirection::NEXT:
      return "NEXT";
    case ActionDirection::PREVIOUS:
    default:
      return "PREVIOUS";
  }
}

bool getKWinBoolProperty(GDBusConnection *bus, const std::string &path,
                         const char *interfaceName, const char *property) {
  GVariant *reply = g_dbus_connection_call_sync(
      bus, "org.kde.KWin", path.c_str(), "org.freedesktop.DBus.Properties",
      "Get", g_variant_new("(ss)", interfaceName, property),
      G_VARIANT_TYPE("(v)"), G_DBUS_CALL_FLAGS_NONE, 1000, nullptr, nullptr);

  if (reply == nullptr) {
    return false;
  }

  GVariant *value = nullptr;
  g_variant_get(reply, "(v)", &value);
  bool result = g_variant_is_of_type(value, G_VARIANT_TYPE_BOOLEAN) &&
                (g_variant_get_boolean(value) != FALSE);
  g_variant_unref(value);
  g_variant_unref(reply);
  return result;
}
}  // namespace

bool KWinWayland::isAvailable() {
  const char *sessionType = std::getenv("XDG_SESSION_TYPE");
  const char *waylandDisplay = std::getenv("WAYLAND_DISPLAY");

  if (sessionType == nullptr || std::string(sessionType) != "wayland" ||
      waylandDisplay == nullptr) {
    return false;
  }

  return KWinScriptBridge::isKWinRunning();
}

KWinWayland::KWinWayland()
    : wayland(std::make_unique<WaylandConnection>()),
      kwin(std::make_unique<KWinScriptBridge>()) {}

std::string KWinWayland::getConnectionName() const {
  return this->wayland->getDisplayName();
}

std::unique_ptr<WindowT> KWinWayland::getWindowUnderCursor() const {
  auto window = std::make_unique<KWinWindowT>();

  // Process any pending Wayland event (outputs added/removed, etc)
  this->wayland->dispatchPending();

  GVariant *result = this->kwin->run(SCRIPT_WINDOW_UNDER_CURSOR);
  if (result == nullptr) {
    return window;
  }

  window->valid = kwin_result::getBool(result, "valid");
  if (window->valid) {
    window->internalId = kwin_result::getString(result, "internalId");
    window->className = kwin_result::getString(result, "resourceClass");
    if (window->className.empty()) {
      window->className = kwin_result::getString(result, "desktopFileName");
    }
    window->geometry = KWinWayland::getRectangle(result, "");
    window->iconGeometry = KWinWayland::getRectangle(result, "icon");
    window->maximized = kwin_result::getBool(result, "maximized");
    window->fullscreen = kwin_result::getBool(result, "fullscreen");
    window->systemWindow = kwin_result::getBool(result, "system");
  }

  g_variant_unref(result);
  return window;
}

std::string KWinWayland::getWindowClassName(const WindowT &window) const {
  return dynamic_cast<const KWinWindowT &>(window).className;
}

Rectangle KWinWayland::getWindowSize(const WindowT &window) const {
  return dynamic_cast<const KWinWindowT &>(window).geometry;
}

bool KWinWayland::isWindowMaximized(const WindowT &window) const {
  return dynamic_cast<const KWinWindowT &>(window).maximized;
}

bool KWinWayland::isWindowFullscreen(const WindowT &window) const {
  return dynamic_cast<const KWinWindowT &>(window).fullscreen;
}

bool KWinWayland::isSystemWindow(const WindowT &window) const {
  return dynamic_cast<const KWinWindowT &>(window).systemWindow;
}

void KWinWayland::maximizeOrRestoreWindow(const WindowT &window) const {
  this->runOnWindow(window, R"JS(
    const maximize = (window.maximizeMode !== 3);
    window.setMaximize(maximize, maximize);
  )JS");
}

void KWinWayland::toggleFullscreenWindow(const WindowT &window) const {
  this->runOnWindow(window, "window.fullScreen = !window.fullScreen;");
}

void KWinWayland::minimizeWindow(const WindowT &window) const {
  this->runOnWindow(window, "window.minimized = true;");
}

Rectangle KWinWayland::minimizeWindowIconSize(const WindowT &window) const {
  return dynamic_cast<const KWinWindowT &>(window).iconGeometry;
}

void KWinWayland::tileWindow(const WindowT &window, bool toTheLeft) const {
  // KWin's quick tiling only works on the active window
  std::string script = "workspace.activeWindow = window;\n";
  script += toTheLeft ? "workspace.slotWindowQuickTileLeft();"
                      : "workspace.slotWindowQuickTileRight();";
  this->runOnWindow(window, script);
}

void KWinWayland::activateWindow(const WindowT &window) const {
  this->runOnWindow(window, "workspace.activeWindow = window;");
}

void KWinWayland::closeWindow(const WindowT &window) const {
  this->runOnWindow(window, "window.closeWindow();");
}

void KWinWayland::sendKeys(const std::vector<std::string> &keycodes,
                           bool isPress) const {
  if (!this->wayland->canSendInput()) {
    tlg::error << "Error performing keyboard shortcut: The compositor doesn't "
                  "allow Touchégg to emulate keyboard events"
               << std::endl;
    return;
  }

  for (const std::string &keycode : keycodes) {
    xkb_keysym_t keysym =
        xkb_keysym_from_name(keycode.c_str(), XKB_KEYSYM_NO_FLAGS);
    if (keysym == XKB_KEY_NoSymbol) {
      keysym =
          xkb_keysym_from_name(keycode.c_str(), XKB_KEYSYM_CASE_INSENSITIVE);
    }

    if (keysym != XKB_KEY_NoSymbol) {
      this->wayland->sendKeysym(keysym, isPress);
    } else {
      tlg::error << "Error performing keyboard shortcut. Unknown key: "
                 << keycode << std::endl;
    }
  }
}

void KWinWayland::sendMouseDown(int button) const {
  this->sendMouseButton(button, true);
}

void KWinWayland::sendMouseUp(int button) const {
  this->sendMouseButton(button, false);
}

void KWinWayland::sendMouseButton(int button, bool isPress) const {
  // X11 button numbers, as documented in the README
  uint32_t linuxButton = 0;
  switch (button) {
    case 1:
      linuxButton = BTN_LEFT;
      break;
    case 2:
      linuxButton = BTN_MIDDLE;
      break;
    case 3:
      linuxButton = BTN_RIGHT;
      break;
    case 8:
      linuxButton = BTN_SIDE;
      break;
    case 9:
      linuxButton = BTN_EXTRA;
      break;
    default:
      tlg::error << "Unsupported mouse button: " << button << std::endl;
      return;
  }

  this->wayland->sendButton(linuxButton, isPress);
}

Rectangle KWinWayland::getDesktopWorkarea() const {
  GVariant *result = this->kwin->run(SCRIPT_OUTPUT_UNDER_CURSOR);
  Rectangle workarea = KWinWayland::getRectangle(result, "workarea");
  if (result != nullptr) {
    g_variant_unref(result);
  }
  return workarea;
}

void KWinWayland::changeDesktop(ActionDirection direction, bool cyclic) const {
  std::string script = "const DIRECTION = \"";
  script += actionDirectionToJs(direction);
  script += "\";\nconst CYCLIC = ";
  script += cyclic ? "true" : "false";
  script += ";\n";
  script += SCRIPT_CHANGE_DESKTOP;

  GVariant *result = this->kwin->run(script);
  if (result != nullptr) {
    g_variant_unref(result);
  }
}

void KWinWayland::showDesktop(bool show) const {
  GDBusConnection *bus = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, nullptr);
  if (bus == nullptr) {
    return;
  }

  GVariant *reply = g_dbus_connection_call_sync(
      bus, "org.kde.KWin", "/KWin", "org.kde.KWin", "showDesktop",
      g_variant_new("(b)", static_cast<gboolean>(show)), nullptr,
      G_DBUS_CALL_FLAGS_NONE, 1000, nullptr, nullptr);
  if (reply != nullptr) {
    g_variant_unref(reply);
  }
  g_object_unref(bus);
}

bool KWinWayland::isShowingDesktop() const {
  GDBusConnection *bus = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, nullptr);
  if (bus == nullptr) {
    return false;
  }

  bool showing =
      getKWinBoolProperty(bus, "/KWin", "org.kde.KWin", "showingDesktop");
  g_object_unref(bus);
  return showing;
}

std::unique_ptr<CairoSurface> KWinWayland::createCairoSurface() const {
  auto [outputName, outputGeometry] = this->getOutputUnderCursor();
  return std::make_unique<WaylandCairoSurface>(this->wayland.get(), outputName,
                                               outputGeometry);
}

bool KWinWayland::isNaturalScrollEnabled(DeviceType deviceType) const {
  if (deviceType == DeviceType::TOUCHSCREEN) {
    return true;
  }

  GDBusConnection *bus = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, nullptr);
  if (bus == nullptr) {
    return false;
  }

  GVariant *reply = g_dbus_connection_call_sync(
      bus, "org.kde.KWin", "/org/kde/KWin/InputDevice",
      "org.freedesktop.DBus.Properties", "Get",
      g_variant_new("(ss)", "org.kde.KWin.InputDeviceManager",
                    "devicesSysNames"),
      G_VARIANT_TYPE("(v)"), G_DBUS_CALL_FLAGS_NONE, 1000, nullptr, nullptr);

  // Like on X11, natural scroll is enabled if it is enabled on any touchpad
  bool enabled = false;
  if (reply != nullptr) {
    GVariant *value = nullptr;
    g_variant_get(reply, "(v)", &value);

    if (g_variant_is_of_type(value, G_VARIANT_TYPE_STRING_ARRAY)) {
      gsize count = 0;
      const gchar **names = g_variant_get_strv(value, &count);
      for (gsize i = 0; i < count && !enabled; i++) {
        std::string path = "/org/kde/KWin/InputDevice/";
        path += names[i];  // NOLINT
        if (getKWinBoolProperty(bus, path, "org.kde.KWin.InputDevice",
                                "touchpad")) {
          enabled = getKWinBoolProperty(bus, path, "org.kde.KWin.InputDevice",
                                        "naturalScroll");
        }
      }
      g_free(static_cast<gpointer>(names));
    }

    g_variant_unref(value);
    g_variant_unref(reply);
  }

  g_object_unref(bus);
  return enabled;
}

GestureDirection KWinWayland::calculateRotation(
    GestureType gestureType, DeviceType deviceType,
    GestureDirection direction) const {
  if (gestureType != GestureType::SWIPE ||
      deviceType != DeviceType::TOUCHSCREEN) {
    return direction;
  }

  this->wayland->dispatchPending();
  auto [outputName, outputGeometry] = this->getOutputUnderCursor();
  const WaylandConnection::Output *output =
      this->wayland->findOutput(outputName);
  if (output == nullptr) {
    return direction;
  }

  // Like RandR, Wayland output transforms are counter-clockwise. Flipped
  // transforms are handled like their rotated equivalent
  switch (output->transform) {
    case WL_OUTPUT_TRANSFORM_90:
    case WL_OUTPUT_TRANSFORM_FLIPPED_90:
      if (direction == GestureDirection::UP) {
        return GestureDirection::RIGHT;
      }
      if (direction == GestureDirection::DOWN) {
        return GestureDirection::LEFT;
      }
      if (direction == GestureDirection::LEFT) {
        return GestureDirection::UP;
      }
      if (direction == GestureDirection::RIGHT) {
        return GestureDirection::DOWN;
      }
      break;
    case WL_OUTPUT_TRANSFORM_180:
    case WL_OUTPUT_TRANSFORM_FLIPPED_180:
      if (direction == GestureDirection::UP) {
        return GestureDirection::DOWN;
      }
      if (direction == GestureDirection::DOWN) {
        return GestureDirection::UP;
      }
      if (direction == GestureDirection::LEFT) {
        return GestureDirection::RIGHT;
      }
      if (direction == GestureDirection::RIGHT) {
        return GestureDirection::LEFT;
      }
      break;
    case WL_OUTPUT_TRANSFORM_270:
    case WL_OUTPUT_TRANSFORM_FLIPPED_270:
      if (direction == GestureDirection::UP) {
        return GestureDirection::LEFT;
      }
      if (direction == GestureDirection::DOWN) {
        return GestureDirection::RIGHT;
      }
      if (direction == GestureDirection::LEFT) {
        return GestureDirection::DOWN;
      }
      if (direction == GestureDirection::RIGHT) {
        return GestureDirection::UP;
      }
      break;
    default:
      break;
  }

  return direction;
}

void KWinWayland::runOnWindow(const WindowT &window,
                              const std::string &script) const {
  const auto &kwinWindow = dynamic_cast<const KWinWindowT &>(window);
  if (!kwinWindow.valid) {
    return;
  }

  std::string body = "const window = findWindow(";
  body += KWinWayland::quote(kwinWindow.internalId);
  body += ");\nif (!window) { return {}; }\n";
  body += script;

  GVariant *result = this->kwin->run(body);
  if (result != nullptr) {
    g_variant_unref(result);
  }
}

std::pair<std::string, Rectangle> KWinWayland::getOutputUnderCursor() const {
  GVariant *result = this->kwin->run(SCRIPT_OUTPUT_UNDER_CURSOR);
  std::string name = kwin_result::getString(result, "name");
  Rectangle geometry = KWinWayland::getRectangle(result, "");
  if (result != nullptr) {
    g_variant_unref(result);
  }
  return {name, geometry};
}

std::string KWinWayland::quote(const std::string &str) {
  // Window IDs are UUIDs like "{6a5c...}", but escape anyway
  std::string quoted = "\"";
  for (char c : str) {
    if (c == '"' || c == '\\') {
      quoted += '\\';
    }
    if (c != '\n' && c != '\r') {
      quoted += c;
    }
  }
  quoted += "\"";
  return quoted;
}

Rectangle KWinWayland::getRectangle(GVariant *dict, const std::string &prefix) {
  // Keys are "x", "width"... or "<prefix>X", "<prefix>Width"...
  auto key = [&prefix](const std::string &name) {
    if (prefix.empty()) {
      return name;
    }
    std::string capitalized = name;
    capitalized[0] = static_cast<char>(std::toupper(capitalized[0]));
    return prefix + capitalized;
  };

  Rectangle rectangle;
  rectangle.x = static_cast<int>(
      std::lround(kwin_result::getDouble(dict, key("x").c_str())));
  rectangle.y = static_cast<int>(
      std::lround(kwin_result::getDouble(dict, key("y").c_str())));
  rectangle.width = static_cast<int>(
      std::lround(kwin_result::getDouble(dict, key("width").c_str())));
  rectangle.height = static_cast<int>(
      std::lround(kwin_result::getDouble(dict, key("height").c_str())));
  return rectangle;
}

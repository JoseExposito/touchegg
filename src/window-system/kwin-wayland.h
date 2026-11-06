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
#ifndef WINDOW_SYSTEM_KWIN_WAYLAND_H_
#define WINDOW_SYSTEM_KWIN_WAYLAND_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "window-system/kwin-script-bridge.h"
#include "window-system/wayland-connection.h"
#include "window-system/window-system.h"

/**
 * Window snapshot taken when the gesture begins.
 */
class KWinWindowT : public WindowT {
 public:
  bool valid = false;
  std::string internalId;
  std::string className;
  Rectangle geometry;
  Rectangle iconGeometry;
  bool maximized = false;
  bool fullscreen = false;
  bool systemWindow = false;
};

/**
 * KDE Plasma Wayland session support.
 *
 * Wayland doesn't allow clients to manage other clients' windows, so this
 * backend relies on KDE specific APIs:
 *  - KWin's JavaScript API (over D-Bus) to inspect and manage windows.
 *  - The org_kde_kwin_fake_input Wayland protocol to emulate input events.
 *  - wlr_layer_shell to draw animations.
 */
class KWinWayland : public WindowSystem {
 public:
  KWinWayland();

  /**
   * @returns If the current session is a KDE Plasma Wayland session.
   */
  static bool isAvailable();

  std::string getConnectionName() const override;
  std::unique_ptr<WindowT> getWindowUnderCursor() const override;
  std::string getWindowClassName(const WindowT &window) const override;
  Rectangle getWindowSize(const WindowT &window) const override;
  bool isWindowMaximized(const WindowT &window) const override;
  bool isWindowFullscreen(const WindowT &window) const override;
  bool isSystemWindow(const WindowT &window) const override;
  void maximizeOrRestoreWindow(const WindowT &window) const override;
  void toggleFullscreenWindow(const WindowT &window) const override;
  void minimizeWindow(const WindowT &window) const override;
  Rectangle minimizeWindowIconSize(const WindowT &window) const override;
  void tileWindow(const WindowT &window, bool toTheLeft) const override;
  void activateWindow(const WindowT &window) const override;
  void closeWindow(const WindowT &window) const override;
  void sendKeys(const std::vector<std::string> &keycodes,
                bool isPress) const override;
  void sendMouseDown(int button) const override;
  void sendMouseUp(int button) const override;
  Rectangle getDesktopWorkarea() const override;
  void changeDesktop(ActionDirection direction, bool cyclic) const override;
  void showDesktop(bool show) const override;
  bool isShowingDesktop() const override;
  std::unique_ptr<CairoSurface> createCairoSurface() const override;
  bool isNaturalScrollEnabled(DeviceType deviceType) const override;
  GestureDirection calculateRotation(GestureType gestureType,
                                     DeviceType deviceType,
                                     GestureDirection direction) const override;

 private:
  std::unique_ptr<WaylandConnection> wayland;
  std::unique_ptr<KWinScriptBridge> kwin;

  /**
   * Run a script on the window, if it is a valid window.
   * The script has access to the window in the "window" variable.
   */
  void runOnWindow(const WindowT &window, const std::string &script) const;

  /**
   * @returns The name and logical geometry of the output under the cursor.
   */
  std::pair<std::string, Rectangle> getOutputUnderCursor() const;

  void sendMouseButton(int button, bool isPress) const;

  static std::string quote(const std::string &str);
  static Rectangle getRectangle(GVariant *dict, const std::string &prefix);
};

#endif  // WINDOW_SYSTEM_KWIN_WAYLAND_H_

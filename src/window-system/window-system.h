/**
 * Copyright 2011 - 2022 José Expósito <jose.exposito89@gmail.com>
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
#ifndef WINDOW_SYSTEM_WINDOW_SYSTEM_H_
#define WINDOW_SYSTEM_WINDOW_SYSTEM_H_

#include <cairo.h>

#include <memory>
#include <string>
#include <vector>

#include "actions/action-direction.h"
#include "gesture/device-type.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"
#include "utils/rectangle.h"
#include "window-system/cairo-surface.h"

/**
 * Abstract window type.
 */
class WindowT {
 public:
  virtual ~WindowT() = default;
};

/**
 * High level abstract interface to the underlying window system.
 * For the moment, and most likely forever, only X11 is supported.
 * However, if in the future it is possible to implement this methods in another
 * window system, like for example Wayland, all the platform specified logic is
 * encapsulated here.
 */
class WindowSystem {
 public:
  virtual ~WindowSystem() = default;

  /**
   * @return The name of the connection to the windowing system.
   */
  virtual std::string getConnectionName() const = 0;

  /**
   * @return Return the window under the cursor/pointer.
   */
  virtual std::unique_ptr<WindowT> getWindowUnderCursor() const = 0;

  /**
   * Returns the window class name.
   * The class name is not the title of the window, it is the unique name the
   * application has. For example, Chrome's class name is "Google-chrome".
   * Under X11 this name can be obtained with the "xprop" command.
   */
  virtual std::string getWindowClassName(const WindowT &window) const = 0;

  /**
   * @returns The size of the window.
   */
  virtual Rectangle getWindowSize(const WindowT &window) const = 0;

  /**
   * @returns If the window is maximized or not.
   */
  virtual bool isWindowMaximized(const WindowT &window) const = 0;

  /**
   * @returns If the window is in fullscreen.
   */
  virtual bool isWindowFullscreen(const WindowT &window) const = 0;

  /**
   * @returns If the window is a system window, like the desktop window, the
   * dock, a panel, etc
   */
  virtual bool isSystemWindow(const WindowT &window) const = 0;

  /**
   * If the window is not maximized, maximize it, otherwise restore its size.
   */
  virtual void maximizeOrRestoreWindow(const WindowT &window) const = 0;

  /**
   * Fullscreen a window if it isn't using the whole screen, otherwise restore
   * its size.
   */
  virtual void toggleFullscreenWindow(const WindowT &window) const = 0;

  /**
   * Minimize a window.
   */
  virtual void minimizeWindow(const WindowT &window) const = 0;

  /**
   * @returns The size of the window icon in the toolbar/dock or similar. Useful
   * to perform minimize animations.
   */
  virtual Rectangle minimizeWindowIconSize(const WindowT &window) const = 0;

  /**
   * Change a window size to use the left or right half of the screen.
   */
  virtual void tileWindow(const WindowT &window, bool toTheLeft) const = 0;

  /**
   * Bring the window to the front.
   */
  virtual void activateWindow(const WindowT &window) const = 0;

  /**
   * Close the window.
   */
  virtual void closeWindow(const WindowT &window) const = 0;

  /**
   * Simulate a key press.
   */
  virtual void sendKeys(const std::vector<std::string> &keycodes,
                        bool isPress) const = 0;

  /**
   * Simulates a mouse click.
   * @param button One of this values:
   * 1 – Left button click
   * 2 – Middle button click
   * 3 – Right button click
   */
  virtual void sendMouseClick(int button) const = 0;

  /**
   * @returns The size of the desktop workarea, ie, the area of the desktop not
   * used by system elements like docks, panels, etc.
   */
  virtual Rectangle getDesktopWorkarea() const = 0;

  /**
   * Changes to the next/previous desktop.
   */
  virtual void changeDesktop(ActionDirection direction, bool cyclic) const = 0;

  /**
   * Show the desktop.
   */
  virtual void showDesktop(bool show) const = 0;

  /**
   * @returns If the desktop is being shown.
   */
  virtual bool isShowingDesktop() const = 0;

  /**
   * Creates a Cairo surface to draw on.
   */
  virtual std::unique_ptr<CairoSurface> createCairoSurface() const = 0;

  /**
   * The libinput backend has access to this property as it is set on libinput.
   * This property should be valid on Wayland, however, on X11 this property is
   * stored on XInput2 and it is not synchronized with the libinput backend.
   * This methods returns the natural scrolling preferences adapted to the
   * current window system.
   * @returns If natural scroll is enabled in the current window system.
   */
  virtual bool isNaturalScrollEnabled(DeviceType deviceType) const = 0;

  /**
   * When a touchscreen is rotated, the gesture direction sent by the daemon
   * doesn't apply the rotation because it doesn't know which backend is used
   * and also because libinput only stores rotation information for trackpoints:
   *
   * "This is currently only available on trackpoints [...]"
   * https://wayland.freedesktop.org/libinput/doc/latest/configuration.html#rotation
   *
   * @returns The direction after applying touchscreen rotation.
   */
  virtual GestureDirection calculateRotation(
      GestureType gestureType, DeviceType deviceType,
      GestureDirection direction) const = 0;
};

#endif  // WINDOW_SYSTEM_WINDOW_SYSTEM_H_

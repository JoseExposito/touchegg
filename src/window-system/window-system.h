/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
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
   * Creates a Cairo surface to draw on.
   * IMPORTANT! Destroy the surface with WindowSystem::destroySurface().
   */
  virtual cairo_surface_t *createSurface() const = 0;

  /**
   * @returns Surface width.
   */
  virtual int getSurfaceWidth(cairo_surface_t *cairoSurface) const = 0;

  /**
   * @returns Surface height.
   */
  virtual int getSurfaceHeight(cairo_surface_t *cairoSurface) const = 0;

  /**
   * Flush the Cairo surface.
   * @param cairoSurface The surface.
   */
  virtual void flushSurface(cairo_surface_t *cairoSurface) const = 0;

  /**
   * Destroy the Cairo surface.
   * @param cairoSurface The surface.
   */
  virtual void destroySurface(cairo_surface_t *cairoSurface) const = 0;

  /**
   * @returns If the window is maximized or not.
   */
  virtual bool isWindowMaximized(const WindowT &window) const = 0;

  /**
   * If the window is not maximized, maximize it, otherwise restore its size.
   */
  virtual void maximizeOrRestoreWindow(const WindowT &window) const = 0;

  /**
   * Minimize a window.
   */
  virtual void minimizeWindow(const WindowT &window) const = 0;
};

#endif  // WINDOW_SYSTEM_WINDOW_SYSTEM_H_

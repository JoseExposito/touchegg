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
#ifndef WINDOW_SYSTEM_X11_CAIRO_SURFACE_H_
#define WINDOW_SYSTEM_X11_CAIRO_SURFACE_H_

#include <X11/X.h>
#include <X11/Xlib.h>
#include <cairo.h>

#include "window-system/cairo-surface.h"

/**
 * X11 cairo surface.
 */
class X11CairoSurface : public CairoSurface {
 public:
  explicit X11CairoSurface(Display *display);
  ~X11CairoSurface();
  cairo_t *getContext() override;
  void flush() override;

 private:
  /**
   * X11 connection.
   */
  Display *display;

  /**
   * X11 window where the animation is drawn.
   */
  Window window = None;

  /**
   * Cairo surface and context for the window.
   */
  cairo_surface_t *windowSurface = nullptr;
  cairo_t *windowContext = nullptr;

  /**
   * Cairo surface and context to draw in memory.
   */
  cairo_surface_t *bufferSurface = nullptr;
  cairo_t *bufferContext = nullptr;
};

#endif  // WINDOW_SYSTEM_X11_CAIRO_SURFACE_H_

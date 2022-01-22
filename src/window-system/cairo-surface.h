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
#ifndef WINDOW_SYSTEM_CAIRO_SURFACE_H_
#define WINDOW_SYSTEM_CAIRO_SURFACE_H_

#include <cairo.h>

#include <iostream>

/**
 * Window system independent cairo surface abstraction.
 */
class CairoSurface {
 public:
  virtual ~CairoSurface() = default;

  /**
   * @returns The cairo context.
   */
  virtual cairo_t *getContext() = 0;

  /**
   * Flush and display on screen.
   */
  virtual void flush() = 0;
};

#endif  // WINDOW_SYSTEM_CAIRO_SURFACE_H_

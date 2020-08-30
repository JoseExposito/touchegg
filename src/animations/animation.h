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
#ifndef ANIMATIONS_ANIMATION_H_
#define ANIMATIONS_ANIMATION_H_

#include <cairo.h>

#include <memory>

#include "window-system/window-system.h"

class Animation {
 public:
  Animation(const WindowSystem &windowSystem, const WindowT &window)
      : windowSystem(windowSystem),
        window(window),
        surface(this->windowSystem.createSurface()),
        cairoContext(cairo_create(this->surface)) {}

  virtual ~Animation() {
    cairo_destroy(this->cairoContext);
    this->windowSystem.destroySurface(this->surface);
  }

  /**
   * Draw the animation on screen.
   * @param percentage A number between 0 and 100 indicating the percentage of
   * the animation.
   */
  virtual void render(int percentage) = 0;

 protected:
  const WindowSystem &windowSystem;
  const WindowT &window;
  cairo_surface_t *surface;
  cairo_t *cairoContext;
};

#endif  // ANIMATIONS_ANIMATION_H_

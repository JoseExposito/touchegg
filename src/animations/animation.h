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
  // TODO(jose) Create always a full-screen surface???
  explicit Animation(const WindowSystem &windowSystem)
      : windowSystem(windowSystem),
        surface(this->windowSystem.createSurface({0, 0, 1000, 1000})),
        cairoContext(cairo_create(this->surface.get())) {}

  virtual ~Animation() { cairo_destroy(this->cairoContext); }

  virtual void render() = 0;

 protected:
  const WindowSystem &windowSystem;
  std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> surface;
  cairo_t *cairoContext;
};

#endif  // ANIMATIONS_ANIMATION_H_

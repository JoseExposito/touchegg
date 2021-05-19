/**
 * Copyright 2011 - 2021 José Expósito <jose.exposito89@gmail.com>
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
#include "animations/custom-action-animation.h"

#include <algorithm>
#include <cmath>
#include <iostream>

CustomActionAnimation::CustomActionAnimation(const WindowSystem &windowSystem,
                                             const WindowT &window, Color color,
                                             Color borderColor,
                                             ActionDirection animationPosition,
                                             std::optional<Script> script)
    : Animation(windowSystem, window), color(color), borderColor(borderColor) {
  Rectangle workarea = this->windowSystem.getDesktopWorkarea();

  this->script = std::move(script);

  maxSize.height = workarea.height;
  maxSize.width = workarea.width;

  maxSize.x = workarea.x;
  maxSize.y = workarea.y;

  switch (animationPosition) {
    case ActionDirection::UP:
      this->angle = M_PI + (M_PI / 2);
      break;
    case ActionDirection::DOWN:
      this->angle = M_PI / 2;
      break;
    case ActionDirection::LEFT:
      this->angle = M_PI;
      break;
    default:
      this->angle = 0;
      break;
  }
}

void CustomActionAnimation::render(double percentage) {
  cairo_t *ctx = this->cairoSurface->getContext();

  // Clear the background
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_set_operator(ctx, CAIRO_OPERATOR_SOURCE);
  cairo_paint(ctx);

    if (this->script) {
      this->script->animate(percentage);
    }

  this->cairoSurface->flush();
}

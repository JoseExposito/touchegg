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
#include "animations/tile-window-animation.h"

#include <algorithm>
#include <iostream>

TileWindowAnimation::TileWindowAnimation(const WindowSystem &windowSystem,
                                         const WindowT &window, Color color,
                                         Color borderColor, bool toTheLeft)
    : Animation(windowSystem, window),
      color(color),
      borderColor(borderColor),
      toTheLeft(toTheLeft) {
  Rectangle workarea = this->windowSystem.getDesktopWorkarea();
  maxSize.x = toTheLeft ? workarea.x : workarea.x + (workarea.width / 2);
  maxSize.y = workarea.y;
  maxSize.width = (workarea.width / 2);
  maxSize.height = workarea.height;
}

void TileWindowAnimation::render(double percentage) {
  cairo_t *ctx = this->cairoSurface->getContext();

  // Clear the background
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_set_operator(ctx, CAIRO_OPERATOR_SOURCE);
  cairo_paint(ctx);

  // Draw the rectangle
  double width = Animation::value(0, maxSize.width, percentage);
  double height = Animation::value(0, maxSize.height, percentage);
  double x = this->toTheLeft ? maxSize.x : maxSize.x + (maxSize.width - width);
  double y = maxSize.y + ((maxSize.height - height) / 2);
  double alpha = Animation::value(0, Animation::MAX_ALPHA, percentage);

  cairo_set_line_width(ctx, 2);
  cairo_set_source_rgba(ctx, borderColor.r(), borderColor.g(), borderColor.b(),
                        alpha);
  cairo_rectangle(ctx, x, y, width, height);
  cairo_stroke_preserve(ctx);

  cairo_set_source_rgba(ctx, color.r(), color.g(), color.b(), alpha);
  cairo_fill(ctx);

  this->cairoSurface->flush();
}

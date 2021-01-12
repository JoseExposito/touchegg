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
#include "animations/minimize-window-animation.h"

#include <algorithm>
#include <iostream>

MinimizeWindowAnimation::MinimizeWindowAnimation(
    const WindowSystem &windowSystem, const WindowT &window, Color color,
    Color borderColor)
    : Animation(windowSystem, window),
      initialSize(this->windowSystem.getWindowSize(this->window)),
      finalSize(this->windowSystem.minimizeWindowIconSize(this->window)),
      color(color),
      borderColor(borderColor) {
  // If the icon size is not set (for example, Ubuntu 20.04) set the finale size
  // to the center of the window
  if (this->finalSize.x == 0 && this->finalSize.y == 0 &&
      this->finalSize.width == 0 && this->finalSize.height == 0) {
    this->finalSize.x = this->initialSize.x + (this->initialSize.width / 2);
    this->finalSize.y = this->initialSize.y + (this->initialSize.height / 2);
    this->finalSize.width = 0;
    this->finalSize.height = 0;
  }
}

void MinimizeWindowAnimation::render(int percentage) {
  cairo_t *ctx = this->cairoSurface->getContext();

  // Clear the background
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_set_operator(ctx, CAIRO_OPERATOR_SOURCE);
  cairo_paint(ctx);

  // Draw the rectangle
  double maxAlpha = 0.6;
  int x = ((percentage * (finalSize.x - initialSize.x)) / 100) + initialSize.x;
  int y = ((percentage * (finalSize.y - initialSize.y)) / 100) + initialSize.y;
  int width = ((percentage * (finalSize.width - initialSize.width)) / 100) +
              initialSize.width;
  int height = ((percentage * (finalSize.height - initialSize.height)) / 100) +
               initialSize.height;
  double alpha = (percentage * maxAlpha) / 100;

  cairo_set_line_width(ctx, 2);
  cairo_set_source_rgba(ctx, borderColor.r(), borderColor.g(), borderColor.b(),
                        alpha);
  cairo_rectangle(ctx, x, y, width, height);
  cairo_stroke_preserve(ctx);

  cairo_set_source_rgba(ctx, color.r(), color.g(), color.b(), alpha);
  cairo_fill(ctx);

  this->cairoSurface->flush();
}

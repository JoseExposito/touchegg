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
#include "animations/maximize-window-animation.h"

MaximizeWindowAnimation::MaximizeWindowAnimation(
    const WindowSystem &windowSystem, const WindowT &window, Color color,
    Color borderColor)
    : Animation(windowSystem, window),
      maxSize(this->windowSystem.getDesktopWorkarea()),
      color(color),
      borderColor(borderColor) {}

void MaximizeWindowAnimation::render(double percentage) {
  cairo_t *ctx = this->cairoSurface->getContext();

  // Clear the background
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_set_operator(ctx, CAIRO_OPERATOR_SOURCE);
  cairo_paint(ctx);

  // Draw the rectangle
  double width = Animation::value(0, maxSize.width, percentage);
  double height = Animation::value(0, maxSize.height, percentage);
  double alpha = Animation::value(0, Animation::MAX_ALPHA, percentage);

  cairo_set_line_width(ctx, 2);
  cairo_set_source_rgba(ctx, borderColor.r(), borderColor.g(), borderColor.b(),
                        alpha);
  cairo_rectangle(ctx, maxSize.x + ((maxSize.width - width) / 2), maxSize.y,
                  width, height);
  cairo_stroke_preserve(ctx);

  cairo_set_source_rgba(ctx, color.r(), color.g(), color.b(), alpha);
  cairo_fill(ctx);

  this->cairoSurface->flush();
}

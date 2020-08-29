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
#include "animations/restore-window-animation.h"

#include <algorithm>

void RestoreWindowAnimation::render(int percentage) {
  cairo_t* ctx = this->cairoContext;

  // Clear the background
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_set_operator(ctx, CAIRO_OPERATOR_SOURCE);
  cairo_paint(ctx);

  // This animation draws a full-screen rectangle with color and a smaller
  // transparent rectangle inside
  int maxWidth = this->windowSystem.getSurfaceWidth(this->surface);
  int maxHeight = this->windowSystem.getSurfaceHeight(this->surface);
  double maxAlpha = 0.6;

  // Full-screen colored rectangle
  double alpha = (percentage * maxAlpha) / 100;
  cairo_set_source_rgba(ctx, 62.0 / 255.0, 159.0 / 255.0, 237.0 / 255.0, alpha);
  cairo_rectangle(ctx, 0, 0, maxWidth, maxHeight);
  cairo_fill(ctx);

  // Calculate the size of the transparent rectangle
  int maxDiff = (5 * std::max(maxWidth, maxHeight)) / 100;
  int width = maxWidth - ((percentage * maxDiff) / 100);
  int height = maxHeight - ((percentage * maxDiff) / 100);

  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_rectangle(ctx, (maxWidth - width) / 2, (maxHeight - height) / 2, width,
                  height);
  cairo_fill(ctx);

  this->windowSystem.flushSurface(this->surface);
}

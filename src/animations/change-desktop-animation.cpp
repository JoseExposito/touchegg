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
#include "animations/change-desktop-animation.h"

#include <algorithm>
#include <cmath>
#include <iostream>

ChangeDesktopAnimation::ChangeDesktopAnimation(
    const WindowSystem &windowSystem, const WindowT &window, Color color,
    Color borderColor, ActionDirection animationPosition)
    : Animation(windowSystem, window), color(color), borderColor(borderColor) {
  Rectangle workarea = this->windowSystem.getDesktopWorkarea();
  maxSize.height = (workarea.height / 7);
  maxSize.width = maxSize.height;

  switch (animationPosition) {
    case ActionDirection::UP:
      maxSize.x = workarea.x + (workarea.width / 2) - (maxSize.width / 2);
      maxSize.y = workarea.y;
      this->angle = M_PI + (M_PI / 2);
      break;
    case ActionDirection::DOWN:
      maxSize.x = workarea.x + (workarea.width / 2) - (maxSize.width / 2);
      maxSize.y = workarea.y + workarea.height - maxSize.height;
      this->angle = M_PI / 2;
      break;
    case ActionDirection::LEFT:
      maxSize.x = workarea.x;
      maxSize.y = workarea.y + (maxSize.height * 3);
      this->angle = M_PI;
      break;
    default:
      maxSize.x = (workarea.x + workarea.width - maxSize.width);
      maxSize.y = workarea.y + (maxSize.height * 3);
      this->angle = 0;
      break;
  }
}

void ChangeDesktopAnimation::render(double percentage) {
  cairo_t *ctx = this->cairoSurface->getContext();

  // Clear the background
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_set_operator(ctx, CAIRO_OPERATOR_SOURCE);
  cairo_paint(ctx);

  // Draw the semi-circle background
  double xCenter = (maxSize.x + (maxSize.width / 2)) +
                   ((maxSize.width / 2) * std::cos(this->angle));
  double yCenter = (maxSize.y + (maxSize.height / 2)) +
                   ((maxSize.height / 2) * std::sin(this->angle));
  double radius = Animation::value(0, (maxSize.width / 2), percentage);
  double angleStart = std::fmod(this->angle + 90 * (M_PI / 180), (2 * M_PI));
  double angleEnd = std::fmod(this->angle + 270 * (M_PI / 180), (2 * M_PI));
  double alpha = Animation::value(0, Animation::MAX_ALPHA, percentage);

  cairo_set_line_width(ctx, 2);
  cairo_set_source_rgba(ctx, borderColor.r(), borderColor.g(), borderColor.b(),
                        alpha);
  cairo_arc(ctx, xCenter, yCenter, radius, angleStart, angleEnd);
  cairo_stroke_preserve(ctx);

  cairo_set_source_rgba(ctx, color.r(), color.g(), color.b(), alpha);
  cairo_fill(ctx);

  // Draw the arrow
  double arrowHeadAngle = (M_PI / 4);
  double arrowLength = (radius / 2);
  double arrowHeadLength = (radius / 3);

  double x1 = (maxSize.x + (maxSize.width / 2)) +
              ((arrowLength / 2) * std::cos(this->angle));
  double y1 = (maxSize.y + (maxSize.height / 2)) +
              ((arrowLength / 2) * std::sin(this->angle));
  double x2 = arrowLength * std::cos(this->angle);
  double y2 = arrowLength * std::sin(this->angle);
  double x3 = -arrowHeadLength * std::cos(this->angle - arrowHeadAngle);
  double y3 = -arrowHeadLength * std::sin(this->angle - arrowHeadAngle);
  double x4 = arrowHeadLength * std::cos(this->angle - arrowHeadAngle);
  double y4 = arrowHeadLength * std::sin(this->angle - arrowHeadAngle);
  double x5 = -arrowHeadLength * std::cos(this->angle + arrowHeadAngle);
  double y5 = -arrowHeadLength * std::sin(this->angle + arrowHeadAngle);

  cairo_set_line_width(ctx, (radius / 10));
  cairo_set_source_rgba(ctx, 0, 0, 0, 0);
  cairo_move_to(ctx, x1, y1);
  cairo_rel_line_to(ctx, x2, y2);
  cairo_rel_move_to(ctx, x3, y3);
  cairo_rel_line_to(ctx, x4, y4);
  cairo_rel_line_to(ctx, x5, y5);
  cairo_stroke(ctx);

  this->cairoSurface->flush();
}

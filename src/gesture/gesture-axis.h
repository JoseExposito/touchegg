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
#ifndef GESTURE_GESTURE_AXIS_H_
#define GESTURE_GESTURE_AXIS_H_

#include <string>
#include "gesture-direction.h"

enum class GestureAxis {
  // A gesture may have an unknown axis until we have more information
  UNKNOWN = 0,

  HORIZONTAL = 1,
  VERTICAL = 2
  // DISTAL = 3

  // Adding a new GestureDirection? Don't forget to add it in
  // gestureAxisToStr and gestureAxisFromStr as well
};

inline std::string gestureAxisToStr(GestureAxis gestureAxis) {
  switch (gestureAxis) {
    case GestureAxis::HORIZONTAL:
      return "HORIZONTAL";
    case GestureAxis::VERTICAL:
      return "VERTICAL";
    // case GestureAxis::DISTAL:
    //   return "DISTAL";
    default:
      return "UNKNOWN";
  }
}

inline GestureAxis gestureAxisFromStr(const std::string &str) {
  if (str == "HORIZONTAL") {
    return GestureAxis::HORIZONTAL;
  }
  if (str == "VERTICAL") {
    return GestureAxis::VERTICAL;
  }
  // if (str == "DISTAL") {
  //   return GestureAxis::DISTAL;
  // }
  return GestureAxis::UNKNOWN;
}

inline GestureAxis gestureAxisFromDirection(GestureDirection gestureDirection) {
  switch (gestureDirection) {
    case GestureDirection::UP:
      return GestureAxis::VERTICAL;
    case GestureDirection::DOWN:
      return GestureAxis::VERTICAL;
    case GestureDirection::LEFT:
      return GestureAxis::HORIZONTAL;
    case GestureDirection::RIGHT:
      return GestureAxis::HORIZONTAL;
    default:
      return GestureAxis::UNKNOWN;
  }
}

#endif  // GESTURE_GESTURE_AXIS_H_

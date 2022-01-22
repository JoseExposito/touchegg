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
#ifndef GESTURE_GESTURE_DIRECTION_H_
#define GESTURE_GESTURE_DIRECTION_H_

#include <string>

enum class GestureDirection {
  // A gesture may have an unknow direction until we have more information
  UNKNOWN = 0,

  // GestureType::SWIPE
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  RIGHT = 4,

  // GestureType::PINCH
  IN = 5,
  OUT = 6,

  // Adding a new GestureDirection? Don't forget to add it in
  // gestureDirectionToStr and gestureDirectionFromStr as well
};

inline std::string gestureDirectionToStr(GestureDirection gestureDirection) {
  switch (gestureDirection) {
    case GestureDirection::UP:
      return "UP";
    case GestureDirection::DOWN:
      return "DOWN";
    case GestureDirection::LEFT:
      return "LEFT";
    case GestureDirection::RIGHT:
      return "RIGHT";
    case GestureDirection::IN:
      return "IN";
    case GestureDirection::OUT:
      return "OUT";
    default:
      return "UNKNOWN";
  }
}

inline GestureDirection gestureDirectionFromStr(const std::string &str) {
  if (str == "UP") {
    return GestureDirection::UP;
  }
  if (str == "DOWN") {
    return GestureDirection::DOWN;
  }
  if (str == "LEFT") {
    return GestureDirection::LEFT;
  }
  if (str == "RIGHT") {
    return GestureDirection::RIGHT;
  }
  if (str == "IN") {
    return GestureDirection::IN;
  }
  if (str == "OUT") {
    return GestureDirection::OUT;
  }
  return GestureDirection::UNKNOWN;
}

#endif  // GESTURE_GESTURE_DIRECTION_H_

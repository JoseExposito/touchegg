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
#ifndef GESTURE_GESTURE_TYPE_H_
#define GESTURE_GESTURE_TYPE_H_

#include <string>

enum class GestureType {
  SWIPE,
  PINCH,
  NOT_SUPPORTED,
  // Adding a new GestureType? Don't forget to add it in gestureTypeToStr and
  // gestureTypeFromStr as well
};

inline std::string gestureTypeToStr(GestureType gestureType) {
  switch (gestureType) {
    case GestureType::SWIPE:
      return "SWIPE";
    case GestureType::PINCH:
      return "PINCH";
    default:
      return "NOT_SUPPORTED";
  }
}

inline GestureType gestureTypeFromStr(const std::string &str) {
  // Support "DRAG" for compatibility with v0 and v1
  if (str == "SWIPE" || str == "DRAG") {
    return GestureType::SWIPE;
  }
  if (str == "PINCH") {
    return GestureType::PINCH;
  }
  return GestureType::NOT_SUPPORTED;
}

#endif  // GESTURE_GESTURE_TYPE_H_

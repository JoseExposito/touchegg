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
#ifndef GESTURE_GATHERER_LIBINPUT_SWIPE_STATE_H_
#define GESTURE_GATHERER_LIBINPUT_SWIPE_STATE_H_

#include "gesture/gesture-direction.h"

/**
 * Data structure to save swipe state in a single place.
 */
struct LibinputSwipeState {
  bool started = false;
  double deltaX = 0;
  double deltaY = 0;
  GestureDirection direction = GestureDirection::UNKNOWN;
  int percentage = 0;

  void reset() {
    started = false;
    deltaX = 0;
    deltaY = 0;
    direction = GestureDirection::UNKNOWN;
    percentage = 0;
  }
};

#endif  // GESTURE_GATHERER_LIBINPUT_SWIPE_STATE_H_

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
#ifndef GESTURE_GESTURE_H_
#define GESTURE_GESTURE_H_

#include "gesture/gesture-type.h"

/**
 * Gestures implementations change depending on the driver/backend. This is the
 * basic interface of a gesture.
 */
class Gesture {
 public:
  virtual ~Gesture() = default;

  /**
   * @returns The gesture type.
   * @see GestureType
   */
  virtual GestureType type() const = 0;

  /**
   * @returns The number of fingers used to perform the gesture.
   */
  virtual int fingers() const = 0;

  /**
   * @returns Gesture change in the X since the its last update.
   */
  virtual double deltaX() const = 0;

  /**
   * @returns Gesture change in the X since the its last update.
   */
  virtual double deltaY() const = 0;
};

#endif  // GESTURE_GESTURE_H_

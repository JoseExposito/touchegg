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
#ifndef GESTURE_GESTURE_H_
#define GESTURE_GESTURE_H_

#include "gesture/device-type.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"

/**
 * Gestures implementations change depending on the driver/backend. This is the
 * basic interface of a gesture.
 */
class Gesture {
 public:
  Gesture(GestureType type, GestureDirection direction, double percentage,
          int fingers, DeviceType performedOnDeviceType, uint64_t elapsedTime)
      : gestureType(type),
        gestureDirection(direction),
        gesturePercentage(percentage),
        gestureFingers(fingers),
        deviceType(performedOnDeviceType),
        gestureElapsedTime(elapsedTime) {}

  /**
   * @returns The gesture type.
   * @see GestureType
   */
  GestureType type() const { return this->gestureType; }

  /**
   * @returns The gesture direction.
   * @see GestureDirection
   */
  GestureDirection direction() const { return this->gestureDirection; }

  /**
   * Percentage of the gesture performed, used for animations.
   * @return Value between 0 and 100.
   */
  double percentage() const { return this->gesturePercentage; }

  /**
   * @returns The number of fingers used to perform the gesture.
   */
  int fingers() const { return this->gestureFingers; }

  /**
   * @returns The device type the gesture was performed on.
   */
  DeviceType performedOnDeviceType() const { return this->deviceType; }

  /**
   * Elapsed time since the beginning of the gesture.
   * @returns The elapsed time in milliseconds.
   */
  uint64_t elapsedTime() const { return this->gestureElapsedTime; }

  /**
   * Set the gesture direction.
   * @see GestureDirection
   */
  void setDirection(GestureDirection direction) {
    this->gestureDirection = direction;
  }

 protected:
  GestureType gestureType = GestureType::NOT_SUPPORTED;
  GestureDirection gestureDirection = GestureDirection::UNKNOWN;
  double gesturePercentage = -1;
  int gestureFingers = -1;
  DeviceType deviceType = DeviceType::UNKNOWN;
  uint64_t gestureElapsedTime = -1;
};

#endif  // GESTURE_GESTURE_H_

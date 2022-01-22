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
#ifndef GESTURE_GATHERER_LIBINPUT_HANDLER_H_
#define GESTURE_GATHERER_LIBINPUT_HANDLER_H_

#include <libinput.h>

#include "gesture-controller/gesture-controller-delegate.h"
#include "gesture-gatherer/libinput-device-info.h"

/**
 * Base class for every libinput handler.
 */
class LininputHandler {
 public:
  explicit LininputHandler(GestureControllerDelegate *gestureController)
      : gestureController(gestureController) {}

 protected:
  GestureControllerDelegate *gestureController;

  /**
   * @return The LibinputDeviceInfo for the device that generated the gesture.
   */
  static LibinputDeviceInfo getDeviceInfo(struct libinput_event *event);

  /**
   * @returns The current epoch time in milliseconds.
   */
  static uint64_t getTimestamp();

  /**
   * @return Elapsed milliseconds since the beginning of the gesture.
   */
  static uint64_t calculateElapsedTime(uint64_t startTimestamp);

  /**
   * @returns The direction of a swipe gesture.
   */
  static GestureDirection calculateSwipeDirection(double deltaX, double deltaY);

  /**
   * @returns The percentage (between 0 and 100) of the gesture animation.
   */
  static double calculateSwipeAnimationPercentage(
      const LibinputDeviceInfo &info, GestureDirection direction, double deltaX,
      double deltaY);

  /**
   * @returns The percentage (between 0 and 100) of the gesture animation.
   */
  static double calculatePinchAnimationPercentage(GestureDirection direction,
                                                  double delta);
};
#endif  // GESTURE_GATHERER_LIBINPUT_HANDLER_H_

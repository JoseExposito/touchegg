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
#ifndef GESTURE_GATHERER_LIBINPUT_TOUCH_HANDLER_H_
#define GESTURE_GATHERER_LIBINPUT_TOUCH_HANDLER_H_

#include <unordered_map>
#include <utility>

#include "gesture-gatherer/libinput-handler.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"

/**
 * Data structure to save touch state in a single place.
 */
struct LibinputTouchState {
  bool started = false;
  GestureType type = GestureType::NOT_SUPPORTED;
  GestureDirection direction = GestureDirection::UNKNOWN;
  uint64_t startTimestamp = 0;
  int startFingers = 0;
  std::unordered_map<int32_t, double> startX;
  std::unordered_map<int32_t, double> startY;
  int currentFingers = 0;
  std::unordered_map<int32_t, double> currentX;
  std::unordered_map<int32_t, double> currentY;
  int tapFingers = 0;

  void reset() {
    started = false;
    type = GestureType::NOT_SUPPORTED;
    direction = GestureDirection::UNKNOWN;
    startTimestamp = 0;
    startFingers = 0;
    tapFingers = 0;

    // Do not reset this data as gestures finish when 1 finger is on the screen
    // startX.clear();
    // startY.clear();
    // currentFingers = 0;
    // currentX.clear();
    // currentY.clear();
  }
};

class LibinputTouchHandler : public LininputHandler {
 public:
  explicit LibinputTouchHandler(GestureControllerDelegate *gestureController)
      : LininputHandler(gestureController) {}

  void handleTouchDown(struct libinput_event *event);
  void handleTouchUp(struct libinput_event *event);
  void handleTouchMotion(struct libinput_event *event);

 private:
  LibinputTouchState state;

  /**
   * @return Average <delta X, delta Y> for the current active fingers.
   */
  std::pair<double, double> getAverageDelta() const;

  /**
   * @returns When the gestures starts, uses "this->state" to differentiate
   * between SWIPE and PINCH gestures.
   */
  GestureType getGestureType() const;

  /**
   * @returns GestureDirection::IN or GestureDirection::OUT.
   */
  GestureDirection calculatePinchDirection() const;

  /**
   * @returns Delta (similar to libinput_event_gesture_get_scale but for touch
   * screens) of a pinch gesture.
   */
  double getPinchDelta() const;

  /**
   * Pinch deltas are calculated "drawing" a bounding box containing every
   * finger involved in the gesture.
   * This method returns that bounding box width (on the X axis) at the
   * beginning of the gesture and in the moment it is called.
   */
  std::pair<double, double> getStartCurrentPinchBBox() const;
};

#endif  // GESTURE_GATHERER_LIBINPUT_TOUCH_HANDLER_H_

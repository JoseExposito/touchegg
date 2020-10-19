/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
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

#include "gesture-gatherer/libinput-handler.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"

/**
 * Data structure to save touch state in a single place.
 */
struct LibinputTouchState {
  bool started = false;
  uint64_t startTimestamp = 0;
  double deltaX = 0;
  double deltaY = 0;
  GestureDirection direction = GestureDirection::UNKNOWN;
  GestureType type = GestureType::NOT_SUPPORTED;
  int percentage = 0;
  int fingers = 0;
  // TODO(jose) On pinch:
  // angleDelta
  // radiusDelta

  void reset() {
    started = false;
    startTimestamp = 0;
    deltaX = 0;
    deltaY = 0;
    direction = GestureDirection::UNKNOWN;
    type = GestureType::NOT_SUPPORTED;
    percentage = 0;
    fingers = 0;
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
};

#endif  // GESTURE_GATHERER_LIBINPUT_TOUCH_HANDLER_H_

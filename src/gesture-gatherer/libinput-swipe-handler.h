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
#ifndef GESTURE_GATHERER_LIBINPUT_SWIPE_HANDLER_H_
#define GESTURE_GATHERER_LIBINPUT_SWIPE_HANDLER_H_

#include <memory>

#include "gesture-controller/gesture-controller-delegate.h"
#include "gesture-gatherer/libinput-handler.h"
#include "gesture/gesture-direction.h"

/**
 * Data structure to save swipe state in a single place.
 */
struct LibinputSwipeState {
  bool started = false;
  uint64_t startTimestamp = 0;
  double deltaX = 0;
  double deltaY = 0;
  GestureDirection direction = GestureDirection::UNKNOWN;
  double percentage = 0;
  int fingers = 0;

  void reset() {
    started = false;
    startTimestamp = 0;
    deltaX = 0;
    deltaY = 0;
    direction = GestureDirection::UNKNOWN;
    percentage = 0;
    fingers = 0;
  }
};

/**
 * Class to handle libinput swipe gestures on a touchpad:
 * https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#swipe-gestures
 */
class LininputSwipeHandler : public LininputHandler {
 public:
  explicit LininputSwipeHandler(GestureControllerDelegate *gestureController)
      : LininputHandler(gestureController) {}

  /**
   * When the user starts a swipe, we still don't know the direction, so here we
   * just reset the state.
   * @param gesture Libinput specialized gesture.
   */
  void handleSwipeBegin(struct libinput_event *event);

  /**
   * On every update we increase or decrease "this->state.deltaX" and
   * "this->state.deltaY". Once any of them passes the configured threshold we
   * send a begin event to the GestureControllerDelegate. Once the threshold is
   * passed we send update events to the GestureControllerDelegate until the
   * gesture ends.
   * @param gesture Libinput specialized gesture.
   */
  void handleSwipeUpdate(struct libinput_event *event);

  /**
   * Send a end event to the GestureControllerDelegate if a gesture was
   * detected.
   * If the gesture didn't pass the threshold we should not notify it.
   * @param gesture Libinput specialized gesture.
   */
  void handleSwipeEnd(struct libinput_event *event);

 private:
  LibinputSwipeState state;
};

#endif  // GESTURE_GATHERER_LIBINPUT_SWIPE_HANDLER_H_

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
#include "gesture-gatherer/libinput-swipe-handler.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include "gesture-gatherer/libinput-device-info.h"
#include "gesture/device-type.h"
#include "gesture/gesture.h"

void LininputSwipeHandler::handleSwipeBegin(struct libinput_event * /*event*/) {
  this->state.reset();
}

void LininputSwipeHandler::handleSwipeUpdate(struct libinput_event *event) {
  struct libinput_event_gesture *gestureEvent =
      libinput_event_get_gesture_event(event);
  this->state.deltaX +=
      libinput_event_gesture_get_dx_unaccelerated(gestureEvent);
  this->state.deltaY +=
      libinput_event_gesture_get_dy_unaccelerated(gestureEvent);

  LibinputDeviceInfo info = LininputHandler::getDeviceInfo(event);

  if (!this->state.started) {
    if (std::abs(this->state.deltaX) > info.startThreshold ||
        std::abs(this->state.deltaY) > info.startThreshold) {
      this->state.started = true;
      this->state.startTimestamp = LininputHandler::getTimestamp();
      this->state.direction = LininputHandler::calculateSwipeDirection(
          this->state.deltaX, this->state.deltaY);
      this->state.percentage =
          LininputHandler::calculateSwipeAnimationPercentage(
              info, this->state.direction, this->state.deltaX,
              this->state.deltaY);
      this->state.fingers =
          libinput_event_gesture_get_finger_count(gestureEvent);
      uint64_t elapsedTime = 0;

      auto gesture = std::make_unique<Gesture>(
          GestureType::SWIPE, this->state.direction, this->state.percentage,
          this->state.fingers, DeviceType::TOUCHPAD, elapsedTime);
      this->gestureController->onGestureBegin(std::move(gesture));
    }
  } else {
    this->state.percentage = LininputHandler::calculateSwipeAnimationPercentage(
        info, this->state.direction, this->state.deltaX, this->state.deltaY);
    uint64_t elapsedTime =
        LininputHandler::calculateElapsedTime(this->state.startTimestamp);

    auto gesture = std::make_unique<Gesture>(
        GestureType::SWIPE, this->state.direction, this->state.percentage,
        this->state.fingers, DeviceType::TOUCHPAD, elapsedTime);
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LininputSwipeHandler::handleSwipeEnd(struct libinput_event *event) {
  if (this->state.started) {
    LibinputDeviceInfo info = LininputHandler::getDeviceInfo(event);
    this->state.percentage = LininputHandler::calculateSwipeAnimationPercentage(
        info, this->state.direction, this->state.deltaX, this->state.deltaY);
    uint64_t elapsedTime =
        LininputHandler::calculateElapsedTime(this->state.startTimestamp);

    auto gesture = std::make_unique<Gesture>(
        GestureType::SWIPE, this->state.direction, this->state.percentage,
        this->state.fingers, DeviceType::TOUCHPAD, elapsedTime);
    this->gestureController->onGestureEnd(std::move(gesture));
  }

  this->state.reset();
}

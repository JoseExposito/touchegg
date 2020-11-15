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
#include "gesture-gatherer/libinput-pinch-handler.h"

#include <algorithm>
#include <utility>

#include "gesture/device-type.h"

void LininputPinchHandler::handlePinchBegin(struct libinput_event * /*event*/) {
  this->state.reset();
}

void LininputPinchHandler::handlePinchUpdate(struct libinput_event *event) {
  struct libinput_event_gesture *gestureEvent =
      libinput_event_get_gesture_event(event);
  this->state.delta = libinput_event_gesture_get_scale(gestureEvent);

  if (!this->state.started) {
    this->state.started = true;
    this->state.startTimestamp = this->getTimestamp();
    this->state.direction =
        (this->state.delta > 1) ? GestureDirection::OUT : GestureDirection::IN;
    this->state.percentage = this->calculatePinchAnimationPercentage(
        this->state.direction, this->state.delta);
    this->state.fingers = libinput_event_gesture_get_finger_count(gestureEvent);
    uint64_t elapsedTime = 0;

    auto gesture = std::make_unique<Gesture>(
        GestureType::PINCH, this->state.direction, this->state.percentage,
        this->state.fingers, DeviceType::TOUCHPAD, elapsedTime);
    this->gestureController->onGestureBegin(std::move(gesture));
  } else {
    this->state.percentage = this->calculatePinchAnimationPercentage(
        this->state.direction, this->state.delta);
    uint64_t elapsedTime =
        this->calculateElapsedTime(this->state.startTimestamp);

    auto gesture = std::make_unique<Gesture>(
        GestureType::PINCH, this->state.direction, this->state.percentage,
        this->state.fingers, DeviceType::TOUCHPAD, elapsedTime);
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LininputPinchHandler::handlePinchEnd(struct libinput_event *event) {
  if (this->state.started) {
    struct libinput_event_gesture *gestureEvent =
        libinput_event_get_gesture_event(event);
    this->state.delta = libinput_event_gesture_get_scale(gestureEvent);
    this->state.percentage = this->calculatePinchAnimationPercentage(
        this->state.direction, this->state.delta);
    uint64_t elapsedTime =
        this->calculateElapsedTime(this->state.startTimestamp);

    auto gesture = std::make_unique<Gesture>(
        GestureType::PINCH, this->state.direction, this->state.percentage,
        this->state.fingers, DeviceType::TOUCHPAD, elapsedTime);
    this->gestureController->onGestureEnd(std::move(gesture));
  }

  this->state.reset();
}

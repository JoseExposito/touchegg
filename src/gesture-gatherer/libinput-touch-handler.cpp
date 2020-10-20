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
#include "gesture-gatherer/libinput-touch-handler.h"

#include <iostream>
#include <memory>
#include <utility>

#include "gesture/gesture.h"

void LibinputTouchHandler::handleTouchDown(struct libinput_event *event) {
  this->state.fingers++;

  struct libinput_event_touch *tEvent = libinput_event_get_touch_event(event);
  int32_t slot = libinput_event_touch_get_slot(tEvent);
  double x = libinput_event_touch_get_x(tEvent);
  double y = libinput_event_touch_get_y(tEvent);
  this->state.initialX[slot] = x;
  this->state.initialY[slot] = y;

  std::cout << "DOWN " << this->state.fingers << std::endl;
  libinput_event_destroy(event);
}

void LibinputTouchHandler::handleTouchUp(struct libinput_event *event) {
  this->state.fingers--;
  std::cout << "UP " << this->state.fingers << std::endl;

  if (!this->state.started) {
    struct libinput_event_touch *tEvent = libinput_event_get_touch_event(event);
    int32_t slot = libinput_event_touch_get_slot(tEvent);
    this->state.initialX.erase(slot);
    this->state.initialY.erase(slot);
  } else {
    if (this->state.fingers == 0) {
      struct libinput_device *device = libinput_event_get_device(event);
      LibinputDeviceInfo info = this->getDeviceInfo(device);

      struct libinput_event_touch *tEvent =
          libinput_event_get_touch_event(event);
      int32_t slot = libinput_event_touch_get_slot(tEvent);
      double x = libinput_event_touch_get_x(tEvent);
      double y = libinput_event_touch_get_y(tEvent);

      double initialX = this->state.initialX.at(slot);
      double initialY = this->state.initialY.at(slot);
      double deltaX = x - initialX;
      double deltaY = y - initialY;

      int percentage = this->calculateSwipeAnimationPercentage(
          info, this->state.direction, deltaX, deltaY);
      uint64_t elapsedTime =
          this->calculateElapsedTime(this->state.startTimestamp);

      auto gesture = std::make_unique<Gesture>(
          this->state.type, this->state.direction, percentage,
          this->state.fingers, deltaX, deltaY, -1, -1, elapsedTime);
      this->gestureController->onGestureEnd(std::move(gesture));

      this->state.reset();
    }
  }

  libinput_event_destroy(event);
}

void LibinputTouchHandler::handleTouchMotion(struct libinput_event *event) {
  struct libinput_event_touch *tEvent = libinput_event_get_touch_event(event);
  int32_t slot = libinput_event_touch_get_slot(tEvent);
  double x = libinput_event_touch_get_x(tEvent);
  double y = libinput_event_touch_get_y(tEvent);

  double initialX = this->state.initialX.at(slot);
  double initialY = this->state.initialY.at(slot);
  double deltaX = x - initialX;
  double deltaY = y - initialY;

  struct libinput_device *device = libinput_event_get_device(event);
  LibinputDeviceInfo info = this->getDeviceInfo(device);

  if (!this->state.started) {
    if (std::abs(deltaX) > info.threshold ||
        std::abs(deltaY) > info.threshold) {
      // TODO(jose) Differentiate SWIPE and PINCH
      this->state.started = true;
      this->state.startTimestamp = this->getTimestamp();
      this->state.type = GestureType::SWIPE;
      this->state.direction = this->calculateSwipeDirection(deltaX, deltaY);
      int percentage = this->calculateSwipeAnimationPercentage(
          info, this->state.direction, deltaX, deltaY);
      uint64_t elapsedTime = 0;

      auto gesture = std::make_unique<Gesture>(
          this->state.type, this->state.direction, percentage,
          this->state.fingers, deltaX, deltaY, -1, -1, elapsedTime);
      this->gestureController->onGestureBegin(std::move(gesture));
    }
  } else {
    int percentage = this->calculateSwipeAnimationPercentage(
        info, this->state.direction, deltaX, deltaY);
    uint64_t elapsedTime =
        this->calculateElapsedTime(this->state.startTimestamp);

    auto gesture = std::make_unique<Gesture>(
        this->state.type, this->state.direction, percentage,
        this->state.fingers, deltaX, deltaY, -1, -1, elapsedTime);
    this->gestureController->onGestureUpdate(std::move(gesture));

    std::cout << "MOTION " << percentage << "%" << std::endl;
  }

  libinput_event_destroy(event);
}

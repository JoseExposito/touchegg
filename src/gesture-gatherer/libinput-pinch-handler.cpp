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

void LininputPinchHandler::handlePinchBegin(
    std::unique_ptr<LibinputGesture> /*gesture*/) {
  this->state.reset();
}

void LininputPinchHandler::handlePinchUpdate(
    std::unique_ptr<LibinputGesture> gesture) {
  if (!this->state.started) {
    this->state.started = true;
    this->state.startTimestamp = this->getTimestamp();
    this->state.delta = gesture->radiusDelta();
    this->state.direction =
        (this->state.delta > 1) ? GestureDirection::OUT : GestureDirection::IN;
    this->state.percentage = this->calculatePinchAnimationPercentage(
        this->state.direction, this->state.delta);

    gesture->setPercentage(this->state.percentage);
    gesture->setDirection(this->state.direction);
    gesture->setElapsedTime(0);
    this->gestureController->onGestureBegin(std::move(gesture));
  } else {
    this->state.delta = gesture->radiusDelta();
    this->state.percentage = this->calculatePinchAnimationPercentage(
        this->state.direction, this->state.delta);

    gesture->setPercentage(this->state.percentage);
    gesture->setDirection(this->state.direction);
    gesture->setElapsedTime(
        this->calculateElapsedTime(this->state.startTimestamp));
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LininputPinchHandler::handlePinchEnd(
    std::unique_ptr<LibinputGesture> gesture) {
  if (this->state.started) {
    this->state.delta = gesture->radiusDelta();
    this->state.percentage = this->calculatePinchAnimationPercentage(
        this->state.direction, this->state.delta);

    gesture->setPercentage(this->state.percentage);
    gesture->setDirection(this->state.direction);
    gesture->setElapsedTime(
        this->calculateElapsedTime(this->state.startTimestamp));
    this->gestureController->onGestureEnd(std::move(gesture));
  }

  this->state.reset();
}

int LininputPinchHandler::calculatePinchAnimationPercentage(
    GestureDirection direction, double delta) const {
  // Delta starts at 1.0:
  // https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#pinch-gestures

  // With direction IN, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 0.0
  if (direction == GestureDirection::IN) {
    return std::min(100, static_cast<int>(std::abs(delta - 1.0) * 100));
  }

  // With direction OUT, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 2.0
  if (direction == GestureDirection::OUT) {
    return std::min(100, static_cast<int>(std::max(0.0, delta - 1.0) * 100));
  }

  return 0;
}

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
#include "gesture-gatherer/libinput-swipe-handler.h"

#include <algorithm>
#include <utility>

#include "gesture-gatherer/libinput-device-info.h"

void LininputSwipeHandler::handleSwipeBegin(
    std::unique_ptr<LibinputGesture> /*gesture*/) {
  this->state.reset();
}

void LininputSwipeHandler::handleSwipeUpdate(
    std::unique_ptr<LibinputGesture> gesture) {
  this->state.deltaX += gesture->deltaX();
  this->state.deltaY += gesture->deltaY();

  if (!this->state.started) {
    LibinputDeviceInfo info = this->getDeviceInfo(*gesture);

    if (std::abs(this->state.deltaX) > info.threshold ||
        std::abs(this->state.deltaY) > info.threshold) {
      this->state.started = true;
      this->state.startTimestamp = this->getTimestamp();
      this->state.direction =
          this->calculateSwipeDirection(this->state.deltaX, this->state.deltaY);
      this->state.percentage = this->calculateSwipeAnimationPercentage(
          *gesture, this->state.direction, this->state.deltaX,
          this->state.deltaY);

      gesture->setPercentage(this->state.percentage);
      gesture->setDirection(this->state.direction);
      gesture->setElapsedTime(0);
      gesture->setTimestamp(this->getTimestamp());
      this->gestureController->onGestureBegin(std::move(gesture));
    }
  } else {
    this->state.percentage = this->calculateSwipeAnimationPercentage(
        *gesture, this->state.direction, this->state.deltaX,
        this->state.deltaY);

    gesture->setPercentage(this->state.percentage);
    gesture->setDirection(this->state.direction);
    gesture->setElapsedTime(
        this->calculateElapsedTime(this->state.startTimestamp));
    gesture->setTimestamp(this->getTimestamp());
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LininputSwipeHandler::handleSwipeEnd(
    std::unique_ptr<LibinputGesture> gesture) {
  if (this->state.started) {
    this->state.percentage = this->calculateSwipeAnimationPercentage(
        *gesture, this->state.direction, this->state.deltaX,
        this->state.deltaY);

    gesture->setPercentage(this->state.percentage);
    gesture->setDirection(this->state.direction);
    gesture->setElapsedTime(
        this->calculateElapsedTime(this->state.startTimestamp));
    gesture->setTimestamp(this->getTimestamp());
    this->gestureController->onGestureEnd(std::move(gesture));
  }

  this->state.reset();
}

GestureDirection LininputSwipeHandler::calculateSwipeDirection(
    double deltaX, double deltaY) const {
  if (std::abs(deltaX) > std::abs(deltaY)) {
    return (deltaX > 0) ? GestureDirection::RIGHT : GestureDirection::LEFT;
  }

  return (deltaY > 0) ? GestureDirection::DOWN : GestureDirection::UP;
}

int LininputSwipeHandler::calculateSwipeAnimationPercentage(
    const LibinputGesture &gesture, GestureDirection direction, double deltaX,
    double deltaY) const {
  LibinputDeviceInfo info = this->getDeviceInfo(gesture);
  double threshold = info.threshold;
  double animationFinishThreshold = info.animationFinishThreshold;

  int max = threshold + animationFinishThreshold;
  int current = 0;

  switch (direction) {
    case GestureDirection::UP:
      current = std::abs(std::min(0.0, deltaY + threshold));
      break;
    case GestureDirection::DOWN:
      current = std::max(0.0, deltaY - threshold);
      break;
    case GestureDirection::LEFT:
      current = std::abs(std::min(0.0, deltaX + threshold));
      break;
    case GestureDirection::RIGHT:
      current = std::max(0.0, deltaX - threshold);
      break;
    default:
      break;
  }

  return std::min((current * 100) / max, 100);
}

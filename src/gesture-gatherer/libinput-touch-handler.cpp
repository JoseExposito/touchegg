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
#include "gesture-gatherer/libinput-touch-handler.h"

#include <libinput.h>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "gesture/device-type.h"
#include "gesture/gesture.h"

namespace {
constexpr int TAP_TIME = 150;
}  // namespace

void LibinputTouchHandler::handleTouchDown(struct libinput_event *event) {
  this->state.currentFingers++;

  struct libinput_event_touch *tEvent = libinput_event_get_touch_event(event);
  int32_t slot = libinput_event_touch_get_slot(tEvent);
  double x = libinput_event_touch_get_x(tEvent);
  double y = libinput_event_touch_get_y(tEvent);

  this->state.startX[slot] = x;
  this->state.startY[slot] = y;
  this->state.currentX[slot] = x;
  this->state.currentY[slot] = y;

  // Save fingers and startTimestamp in case it is a TAP gesture
  this->state.tapFingers = this->state.currentFingers;
  if (this->state.currentFingers == 1) {
    this->state.startTimestamp = LininputHandler::getTimestamp();
  }
}

void LibinputTouchHandler::handleTouchUp(struct libinput_event *event) {
  this->state.currentFingers--;

  struct libinput_event_touch *tEvent = libinput_event_get_touch_event(event);
  int32_t slot = libinput_event_touch_get_slot(tEvent);
  uint64_t elapsedTime =
      LininputHandler::calculateElapsedTime(this->state.startTimestamp);

  // TAP
  if (!this->state.started && this->state.currentFingers == 0 &&
      this->state.tapFingers >= 2 && elapsedTime < TAP_TIME) {
    auto gestureBegin = std::make_unique<Gesture>(
        GestureType::TAP, GestureDirection::UNKNOWN, 100,
        this->state.tapFingers, DeviceType::TOUCHSCREEN, elapsedTime);
    this->gestureController->onGestureBegin(std::move(gestureBegin));

    auto gestureEnd = std::make_unique<Gesture>(
        GestureType::TAP, GestureDirection::UNKNOWN, 100,
        this->state.tapFingers, DeviceType::TOUCHSCREEN, elapsedTime);
    this->gestureController->onGestureEnd(std::move(gestureEnd));

    this->state.reset();
  }

  // SWIPE and PINCH
  if (this->state.started && this->state.currentFingers == 1) {
    LibinputDeviceInfo info = LininputHandler::getDeviceInfo(event);

    std::pair<double, double> deltaPair = this->getAverageDelta();
    double deltaX = deltaPair.first;
    double deltaY = deltaPair.second;

    double percentage =
        (this->state.type == GestureType::SWIPE)
            ? LininputHandler::calculateSwipeAnimationPercentage(
                  info, this->state.direction, deltaX, deltaY)
            : LininputHandler::calculatePinchAnimationPercentage(
                  this->state.direction, this->getPinchDelta());

    auto gesture = std::make_unique<Gesture>(
        this->state.type, this->state.direction, percentage,
        this->state.startFingers, DeviceType::TOUCHSCREEN, elapsedTime);
    this->gestureController->onGestureEnd(std::move(gesture));

    this->state.reset();
  }

  this->state.startX.erase(slot);
  this->state.startY.erase(slot);
  this->state.currentX.erase(slot);
  this->state.currentY.erase(slot);
}

void LibinputTouchHandler::handleTouchMotion(struct libinput_event *event) {
  LibinputDeviceInfo info = LininputHandler::getDeviceInfo(event);
  struct libinput_event_touch *tEvent = libinput_event_get_touch_event(event);
  int32_t slot = libinput_event_touch_get_slot(tEvent);

  this->state.currentX[slot] = libinput_event_touch_get_x(tEvent);
  this->state.currentY[slot] = libinput_event_touch_get_y(tEvent);

  std::pair<double, double> deltaPair = this->getAverageDelta();
  double deltaX = deltaPair.first;
  double deltaY = deltaPair.second;

  if (!this->state.started) {
    if (this->state.currentFingers >= 2 &&
        (std::abs(deltaX) > info.startThreshold ||
         std::abs(deltaY) > info.startThreshold)) {
      this->state.started = true;
      this->state.startFingers = this->state.currentFingers;
      this->state.startTimestamp = LininputHandler::getTimestamp();
      this->state.type = this->getGestureType();
      this->state.direction =
          (this->state.type == GestureType::SWIPE)
              ? LininputHandler::calculateSwipeDirection(deltaX, deltaY)
              : this->calculatePinchDirection();

      // Once the direction is calculated, save the currentX/Y as startX/Y so
      // the startThreshold is not included in the percentage calculations
      double percentage = 0;
      this->state.startX = this->state.currentX;
      this->state.startY = this->state.currentY;

      auto gesture = std::make_unique<Gesture>(
          this->state.type, this->state.direction, percentage,
          this->state.startFingers, DeviceType::TOUCHSCREEN, 0);
      this->gestureController->onGestureBegin(std::move(gesture));
    }
  } else {
    double percentage =
        (this->state.type == GestureType::SWIPE)
            ? LininputHandler::calculateSwipeAnimationPercentage(
                  info, this->state.direction, deltaX, deltaY)
            : LininputHandler::calculatePinchAnimationPercentage(
                  this->state.direction, this->getPinchDelta());
    uint64_t elapsedTime =
        LininputHandler::calculateElapsedTime(this->state.startTimestamp);

    auto gesture = std::make_unique<Gesture>(
        this->state.type, this->state.direction, percentage,
        this->state.startFingers, DeviceType::TOUCHSCREEN, elapsedTime);
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

std::pair<double, double> LibinputTouchHandler::getAverageDelta() const {
  if (this->state.startX.empty() || this->state.startY.empty()) {
    return std::make_pair(0, 0);
  }

  double deltaX = 0;
  double deltaY = 0;

  for (const auto &pair : this->state.startX) {
    int32_t slot = pair.first;
    deltaX += this->state.currentX.at(slot) - this->state.startX.at(slot);
    deltaY += this->state.currentY.at(slot) - this->state.startY.at(slot);
  }

  deltaX /= this->state.startX.size();
  deltaY /= this->state.startY.size();

  return std::make_pair(deltaX, deltaY);
}

GestureType LibinputTouchHandler::getGestureType() const {
  // Store every finger dominant axis (X = 1; Y = -1) and delta
  std::vector<int> axis;
  std::vector<double> delta;

  for (const auto &pair : this->state.startX) {
    int32_t slot = pair.first;
    double diffX = this->state.currentX.at(slot) - this->state.startX.at(slot);
    double diffY = this->state.currentY.at(slot) - this->state.startY.at(slot);

    if (std::abs(diffX) > std::abs(diffY)) {
      axis.push_back(1);
      delta.push_back(diffX);
    } else {
      axis.push_back(-1);
      delta.push_back(diffY);
    }
  }

  // In a SWIPE gesture, every finger has the same dominant axis and a positive
  // or negative dominant delta
  bool sameAxis =
      std::all_of(axis.cbegin(), axis.cend(), [](int i) { return i > 0; }) ||
      std::all_of(axis.cbegin(), axis.cend(), [](int i) { return i < 0; });
  if (!sameAxis) {
    return GestureType::PINCH;
  }

  bool sameDir =
      std::all_of(delta.cbegin(), delta.cend(), [](int i) { return i > 0; }) ||
      std::all_of(delta.cbegin(), delta.cend(), [](int i) { return i < 0; });
  if (!sameDir) {
    return GestureType::PINCH;
  }

  return GestureType::SWIPE;
}

GestureDirection LibinputTouchHandler::calculatePinchDirection() const {
  auto pair = this->getStartCurrentPinchBBox();
  return (pair.first < pair.second) ? GestureDirection::OUT
                                    : GestureDirection::IN;
}

double LibinputTouchHandler::getPinchDelta() const {
  // Delta is 1.0 at the start of the gesture (pair.first)
  // If the user pinch in, delta is 0.0 when both fingers are together
  // Delta increases if the user pinch out
  auto pair = this->getStartCurrentPinchBBox();
  return (pair.second / pair.first);
}

std::pair<double, double> LibinputTouchHandler::getStartCurrentPinchBBox()
    const {
  std::vector<double> start(this->state.startX.size());
  std::transform(this->state.startX.begin(), this->state.startX.end(),
                 start.begin(), [](const auto &pair) { return pair.second; });
  auto startPair = std::minmax_element(start.begin(), start.end());
  double startMin = *startPair.first;
  double startMax = *startPair.second;

  std::vector<double> current(this->state.currentX.size());
  std::transform(this->state.currentX.begin(), this->state.currentX.end(),
                 current.begin(), [](const auto &pair) { return pair.second; });
  auto currentPair =
      std::minmax_element(std::begin(current), std::end(current));
  double currentMin = *currentPair.first;
  double currentMax = *currentPair.second;

  double startBBoxWidth = startMax - startMin;
  double currentBBoxWidth = currentMax - currentMin;

  return std::make_pair(startBBoxWidth, currentBBoxWidth);
}

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
#include "gesture-gatherer/libinput-handler.h"

#include <algorithm>
#include <chrono>  // NOLINT

LibinputDeviceInfo LininputHandler::getDeviceInfo(
    struct libinput_event *event) {
  LibinputDeviceInfo info;

  // Get the precalculated thresholds
  struct libinput_device *device = libinput_event_get_device(event);
  void *userData = libinput_device_get_user_data(device);

  if (userData != nullptr) {
    auto *aux = static_cast<LibinputDeviceInfo *>(userData);
    info.startThreshold = aux->startThreshold;
    info.finishThresholdHorizontal = aux->finishThresholdHorizontal;
    info.finishThresholdVertical = aux->finishThresholdVertical;
  }

  return info;
}

uint64_t LininputHandler::getTimestamp() {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  uint64_t millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
  return millis;
}

uint64_t LininputHandler::calculateElapsedTime(uint64_t startTimestamp) {
  return LininputHandler::getTimestamp() - startTimestamp;
}

GestureDirection LininputHandler::calculateSwipeDirection(double deltaX,
                                                          double deltaY) {
  if (std::abs(deltaX) > std::abs(deltaY)) {
    return (deltaX > 0) ? GestureDirection::RIGHT : GestureDirection::LEFT;
  }

  return (deltaY > 0) ? GestureDirection::DOWN : GestureDirection::UP;
}

double LininputHandler::calculateSwipeAnimationPercentage(
    const LibinputDeviceInfo &info, GestureDirection direction, double deltaX,
    double deltaY) {
  double startThreshold = info.startThreshold;
  double finishThreshold = (direction == GestureDirection::LEFT ||
                            direction == GestureDirection::RIGHT)
                               ? info.finishThresholdHorizontal
                               : info.finishThresholdVertical;

  double max = startThreshold + finishThreshold;
  double current = 0;

  switch (direction) {
    case GestureDirection::UP:
      current = std::abs(std::min(0.0, deltaY + startThreshold));
      break;
    case GestureDirection::DOWN:
      current = std::max(0.0, deltaY - startThreshold);
      break;
    case GestureDirection::LEFT:
      current = std::abs(std::min(0.0, deltaX + startThreshold));
      break;
    case GestureDirection::RIGHT:
      current = std::max(0.0, deltaX - startThreshold);
      break;
    default:
      break;
  }

  return std::min((current * 100) / max, 100.0);
}

double LininputHandler::calculatePinchAnimationPercentage(
    GestureDirection direction, double delta) {
  // Delta starts at 1.0:
  // https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#pinch-gestures

  // With direction IN, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 0.0
  if (direction == GestureDirection::IN) {
    double nDelta = std::min(1.0, delta);
    return std::min(100.0, std::abs(nDelta - 1.0) * 100);
  }

  // With direction OUT, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 2.0
  if (direction == GestureDirection::OUT) {
    double nDelta = std::min(2.0, delta);
    return std::min(100.0, std::max(0.0, nDelta - 1.0) * 100);
  }

  return 0;
}

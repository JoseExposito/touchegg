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
#include "gesture-gatherer/libinput-handler.h"

#include <algorithm>
#include <chrono>  // NOLINT

LibinputDeviceInfo LininputHandler::getDeviceInfo(
    struct libinput_event *event) const {
  LibinputDeviceInfo info;

  // Get the precalculated thresholds
  struct libinput_device *device = libinput_event_get_device(event);
  void *userData = libinput_device_get_user_data(device);

  if (userData != nullptr) {
    auto aux = static_cast<LibinputDeviceInfo *>(userData);
    info.threshold = aux->threshold;
    info.animationFinishThreshold = aux->animationFinishThreshold;
  }

  return info;
}

bool LininputHandler::isNaturalScrollEnabled(
    struct libinput_event *event) const {
  struct libinput_device *device = libinput_event_get_device(event);

  // If the device does not support natural scrolling, fallback to true. For
  // example, a touchscreen.
  int supportsNaturalScroll =
      libinput_device_config_scroll_has_natural_scroll(device);
  if (supportsNaturalScroll == 0) {
    return true;
  }

  int mode = libinput_device_config_scroll_get_natural_scroll_enabled(device);
  return (mode != 0);
}

uint64_t LininputHandler::getTimestamp() const {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  uint64_t millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
  return millis;
}

uint64_t LininputHandler::calculateElapsedTime(uint64_t startTimestamp) const {
  return this->getTimestamp() - startTimestamp;
}

GestureDirection LininputHandler::calculateSwipeDirection(double deltaX,
                                                          double deltaY) const {
  if (std::abs(deltaX) > std::abs(deltaY)) {
    return (deltaX > 0) ? GestureDirection::RIGHT : GestureDirection::LEFT;
  }

  return (deltaY > 0) ? GestureDirection::DOWN : GestureDirection::UP;
}

int LininputHandler::calculateSwipeAnimationPercentage(
    const LibinputDeviceInfo &info, GestureDirection direction, double deltaX,
    double deltaY) const {
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

int LininputHandler::calculatePinchAnimationPercentage(
    GestureDirection direction, double delta) const {
  // Delta starts at 1.0:
  // https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#pinch-gestures

  // With direction IN, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 0.0
  if (direction == GestureDirection::IN) {
    double nDelta = std::min(1.0, delta);
    return std::min(100, static_cast<int>(std::abs(nDelta - 1.0) * 100));
  }

  // With direction OUT, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 2.0
  if (direction == GestureDirection::OUT) {
    double nDelta = std::min(2.0, delta);
    return std::min(100, static_cast<int>(std::max(0.0, nDelta - 1.0) * 100));
  }

  return 0;
}

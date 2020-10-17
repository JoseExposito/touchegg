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

#include <chrono>  // NOLINT

LibinputDeviceInfo LininputHandler::getDeviceInfo(
    const LibinputGesture &gesture) const {
  LibinputDeviceInfo info;

  // Get the precalculated thresholds
  struct libinput_device *device = gesture.getDevice();
  void *userData = libinput_device_get_user_data(device);

  if (userData != nullptr) {
    auto aux = static_cast<LibinputDeviceInfo *>(userData);
    info.threshold = aux->threshold;
    info.animationFinishThreshold = aux->animationFinishThreshold;
  }

  return info;
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

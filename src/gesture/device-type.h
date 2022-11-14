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
#ifndef GESTURE_DEVICE_TYPE_H_
#define GESTURE_DEVICE_TYPE_H_

#include <string>

enum class DeviceType {
  UNKNOWN = 0,
  TOUCHPAD = 1,
  TOUCHSCREEN = 2,

  // Adding a new device type? Don't forget to add it in deviceTypeToStr and
  // deviceTypeFromStr
};

inline std::string deviceTypeToStr(DeviceType deviceType) {
  switch (deviceType) {
    case DeviceType::TOUCHPAD:
      return "TOUCHPAD";
    case DeviceType::TOUCHSCREEN:
      return "TOUCHSCREEN";
    default:
      return "UNKNOWN";
  }
}

inline DeviceType deviceTypeFromStr(const std::string &str) {
  if (str == "TOUCHPAD") {
    return DeviceType::TOUCHPAD;
  }
  if (str == "TOUCHSCREEN") {
    return DeviceType::TOUCHSCREEN;
  }
  return DeviceType::UNKNOWN;
}

#endif  // GESTURE_DEVICE_TYPE_H_

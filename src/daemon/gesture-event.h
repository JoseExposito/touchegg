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
#ifndef DAEMON_GESTURE_EVENT_H_
#define DAEMON_GESTURE_EVENT_H_

#include <string>

#include "gesture/device-type.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"

/**
 * Unix domain socket (abstract namespace).
 */
static const std::string SOCKET_NAME{"\0/touchegg", 10};  // NOLINT

/**
 * Event type sent through the socket.
 */
enum class GestureEventType {
  UNKNOWN = 0,
  BEGIN = 1,
  UPDATE = 2,
  END = 3,
};

/**
 * Event sent through the socket.
 * Clients must read first the "eventSize" and the as many bytes as specified to
 * ensure backward compatibility.
 */
struct GestureEvent {
  // Warning: Do NOT change the order of this fields, add new fields always at
  //          the end or the protocol will not be backward compatible!
  uint32_t eventSize = 0;
  GestureEventType eventType = GestureEventType::UNKNOWN;
  GestureType type = GestureType::NOT_SUPPORTED;
  GestureDirection direction = GestureDirection::UNKNOWN;
  int percentage = 0;
  int fingers = 0;
  uint64_t elapsedTime = 0;
  DeviceType performedOnDeviceType = DeviceType::UNKNOWN;
};

#endif  // DAEMON_GESTURE_EVENT_H_

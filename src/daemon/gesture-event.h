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
  BEGIN,
  UPDATE,
  END,
  UNKNOWN,
};

/**
 * Event sent through the socket.
 */
struct GestureEvent {
  GestureEventType eventType = GestureEventType::UNKNOWN;
  GestureType type = GestureType::NOT_SUPPORTED;
  GestureDirection direction = GestureDirection::UNKNOWN;
  int percentage = 0;
  int fingers = 0;
  double deltaX = 0;
  double deltaY = 0;
  double angleDelta = 0;
  double radiusDelta = 0;
  uint64_t elapsedTime = 0;
};

#endif  // DAEMON_GESTURE_EVENT_H_

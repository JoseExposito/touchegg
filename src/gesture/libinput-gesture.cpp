/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#include "gesture/libinput-gesture.h"

#include <iostream>

LibinputGesture::LibinputGesture(struct libinput_event *event)
    : event(event), gestureEvent(libinput_event_get_gesture_event(event)) {}

LibinputGesture::~LibinputGesture() { libinput_event_destroy(this->event); }

GestureType LibinputGesture::type() {
  libinput_event_type eventType = libinput_event_get_type(this->event);
  switch (eventType) {
    case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
    case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE:
    case LIBINPUT_EVENT_GESTURE_SWIPE_END:
      return GestureType::SWIPE;

    case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
    case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE:
    case LIBINPUT_EVENT_GESTURE_PINCH_END:
      return GestureType::PINCH;

    default:
      std::cout << "Error: LibinputGesture type " << eventType
                << " is not supported" << std::endl;
      return GestureType::NOT_SUPPORTED;
  }
}

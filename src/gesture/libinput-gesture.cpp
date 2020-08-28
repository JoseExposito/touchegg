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
    : event(event),
      gestureEvent(libinput_event_get_gesture_event(event)),
      gestureDirection(GestureDirection::UNKNOWN),
      animationPercentage(0) {}

LibinputGesture::~LibinputGesture() { libinput_event_destroy(this->event); }

GestureType LibinputGesture::type() const {
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

GestureDirection LibinputGesture::direction() const {
  return this->gestureDirection;
}

int LibinputGesture::percentage() const { return this->animationPercentage; }

int LibinputGesture::fingers() const {
  return libinput_event_gesture_get_finger_count(this->gestureEvent);
}

double LibinputGesture::deltaX() const {
  return libinput_event_gesture_get_dx(this->gestureEvent);
}

double LibinputGesture::deltaY() const {
  return libinput_event_gesture_get_dy(this->gestureEvent);
}

double LibinputGesture::angleDelta() const {
  if (this->type() != GestureType::PINCH) {
    return 0;
  }

  return libinput_event_gesture_get_angle_delta(this->gestureEvent);
}

double LibinputGesture::radiusDelta() const {
  if (this->type() != GestureType::PINCH) {
    return 0;
  }

  return libinput_event_gesture_get_scale(this->gestureEvent);
}

void LibinputGesture::setDirection(GestureDirection direction) {
  this->gestureDirection = direction;
}

void LibinputGesture::setPercentage(int percentage) {
  this->animationPercentage = percentage;
}

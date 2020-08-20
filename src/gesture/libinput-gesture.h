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
#ifndef GESTURE_LIBINPUT_GESTURE_H_
#define GESTURE_LIBINPUT_GESTURE_H_

#include <libinput.h>

#include "gesture/gesture-type.h"
#include "gesture/gesture.h"

/**
 * Libinput backend Gesture implementation.
 */
class LibinputGesture : public Gesture {
 public:
  explicit LibinputGesture(struct libinput_event *event);
  ~LibinputGesture();
  GestureType type() override;

 private:
  struct libinput_event *event;
  struct libinput_event_gesture *gestureEvent;
};

#endif  // GESTURE_LIBINPUT_GESTURE_H_

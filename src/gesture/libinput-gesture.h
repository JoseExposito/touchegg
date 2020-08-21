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

#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"
#include "gesture/gesture.h"

/**
 * Libinput backend Gesture implementation.
 * @see Gesture
 */
class LibinputGesture : public Gesture {
 public:
  /**
   * Default contructor, takes the libinput raw event.
   * Memory cleanup is handled by this class.
   * @param Libinput general event.
   */
  explicit LibinputGesture(struct libinput_event *event);

  ~LibinputGesture();

  GestureType type() const override;

  GestureDirection direction() const override;

  int fingers() const override;

  double deltaX() const override;

  double deltaY() const override;

  double angleDelta() const override;

  double radiusDelta() const override;

  /**
   * The direction is not implicit in the libinput_event_gesture, instead
   * LibinputGestureGatherer is in charge of set it once a certain threshold is
   * crossed.
   */
  void setDirection(GestureDirection direction);

 private:
  /**
   * Pointer to the libinput event with the gesture information.
   */
  struct libinput_event *event;

  /**
   * Pointer to the gesture libinput event, obtained from this->event.
   */
  struct libinput_event_gesture *gestureEvent;

  /**
   * Gesture direction. Defaults to GestureDirection::UNKNOWN unless it is set
   * from the outside.
   */
  GestureDirection gestureDirection;
};

#endif  // GESTURE_LIBINPUT_GESTURE_H_

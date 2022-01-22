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
#ifndef GESTURE_CONTROLLER_GESTURE_CONTROLLER_DELEGATE_H_
#define GESTURE_CONTROLLER_GESTURE_CONTROLLER_DELEGATE_H_

#include <memory>

#include "gesture/gesture.h"

/**
 * Instead of passing the GestureController to the GestureGatherer, this
 * delegate interface is passed instead.
 * This interface allows us to decouple the GestureController implementation
 * from the GestureGatherer exposing the minimal interface of the last.
 */
class GestureControllerDelegate {
 public:
  virtual ~GestureControllerDelegate() = default;

  virtual void onGestureBegin(std::unique_ptr<Gesture> gesture) = 0;
  virtual void onGestureUpdate(std::unique_ptr<Gesture> gesture) = 0;
  virtual void onGestureEnd(std::unique_ptr<Gesture> gesture) = 0;
};

#endif  // GESTURE_CONTROLLER_GESTURE_CONTROLLER_DELEGATE_H_

/**
 * Copyright 2011 - 2021 José Expósito <jose.exposito89@gmail.com>
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

#include "actions/custom-action.h"

#include <memory>
#include <string>

#include "animations/custom-action-animation.h"

void CustomAction::onGestureBegin(const Gesture& gesture) {
  if (this->settings.count("direction") == 1) {
    this->direction = actionDirectionFromStr(this->settings.at("direction"));
  }

  if (this->settings.count("script") == 1) {
    Script src(this->settings.at("script"));
//    Script src("/usr/lib/x86_64-linux-gnu/libm.so.6");
    this->script = src;
  }

  if (this->animate) {
    ActionDirection animationPosition = ActionDirection::UNKNOWN;

    if (this->settings.count("animationPosition") == 1) {
      animationPosition =
          actionDirectionFromStr(this->settings.at("animationPosition"));
    } else {
      // If animation position is unset, fallback to the action direction
      switch (this->direction) {
        case ActionDirection::AUTO:
        case ActionDirection::UP:
        case ActionDirection::DOWN:
        case ActionDirection::LEFT:
        case ActionDirection::RIGHT:
          animationPosition = this->direction;
          break;
        case ActionDirection::NEXT:
          animationPosition = ActionDirection::RIGHT;
          break;
        case ActionDirection::PREVIOUS:
        default:
          animationPosition = ActionDirection::LEFT;
          break;
      }
    }

    animationPosition = (animationPosition == ActionDirection::AUTO)
                            ? this->getAnimationAutoDirection(gesture)
                            : animationPosition;

    this->animation = std::make_unique<CustomActionAnimation>(
        this->windowSystem, this->window, this->color, this->borderColor,
        animationPosition);

    if (this->script) {
      this->script->gesture_start(this->settings, this->config);
    }
  }
}

void CustomAction::executeAction(const Gesture& gesture) {
  ActionDirection actionDirection = (this->direction == ActionDirection::AUTO)
                                        ? this->getActionAutoDirection(gesture)
                                        : this->direction;

  this->script->gesture_end(actionDirection);
}

ActionDirection CustomAction::getAnimationAutoDirection(
    const Gesture& gesture) const {
  bool natural = this->windowSystem.isNaturalScrollEnabled(
      gesture.performedOnDeviceType());

  switch (gesture.direction()) {
    case GestureDirection::UP:
      return natural ? ActionDirection::DOWN : ActionDirection::UP;
    case GestureDirection::DOWN:
      return natural ? ActionDirection::UP : ActionDirection::DOWN;
    case GestureDirection::RIGHT:
      return natural ? ActionDirection::LEFT : ActionDirection::RIGHT;
    case GestureDirection::LEFT:
    default:
      return natural ? ActionDirection::RIGHT : ActionDirection::LEFT;
  }
}

ActionDirection CustomAction::getActionAutoDirection(
    const Gesture& gesture) const {
  bool natural = this->windowSystem.isNaturalScrollEnabled(
      gesture.performedOnDeviceType());

  switch (gesture.direction()) {
    case GestureDirection::LEFT:
    case GestureDirection::UP:
      return natural ? ActionDirection::NEXT : ActionDirection::PREVIOUS;
    default:
      return natural ? ActionDirection::PREVIOUS : ActionDirection::NEXT;
  }
}

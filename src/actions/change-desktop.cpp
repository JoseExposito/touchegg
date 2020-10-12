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
#include "actions/change-desktop.h"

#include <memory>
#include <string>

#include "animations/change-desktop-animation.h"

void ChangeDesktop::onGestureBegin(const Gesture& /*gesture*/) {
  if (this->settings.count("direction") == 1) {
    this->direction = actionDirectionFromStr(this->settings.at("direction"));
  }

  if (this->animate) {
    ActionDirection animationPosition = ActionDirection::UNKNOWN;

    if (this->settings.count("animationPosition") == 1) {
      animationPosition =
          actionDirectionFromStr(this->settings.at("animationPosition"));
    } else {
      // If animation position is unset, fallback to the action direction
      switch (this->direction) {
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

    this->animation = std::make_unique<ChangeDesktopAnimation>(
        this->windowSystem, this->window, this->color, this->borderColor,
        animationPosition);
  }
}

void ChangeDesktop::executeAction(const Gesture& /*gesture*/) {
  this->windowSystem.changeDesktop(this->direction);
}

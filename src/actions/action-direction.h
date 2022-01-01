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
#ifndef ACTIONS_ACTION_DIRECTION_H_
#define ACTIONS_ACTION_DIRECTION_H_

#include <string>

enum class ActionDirection {
  UNKNOWN,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  PREVIOUS,
  NEXT,
  AUTO,
  // Adding a new ActionDirection? Don't forget to add it in
  // actionDirectionFromStr
};

inline ActionDirection actionDirectionFromStr(const std::string &str) {
  if (str == "up") {
    return ActionDirection::UP;
  }
  if (str == "down") {
    return ActionDirection::DOWN;
  }
  if (str == "left") {
    return ActionDirection::LEFT;
  }
  if (str == "right") {
    return ActionDirection::RIGHT;
  }
  if (str == "previous") {
    return ActionDirection::PREVIOUS;
  }
  if (str == "next") {
    return ActionDirection::NEXT;
  }
  if (str == "auto") {
    return ActionDirection::AUTO;
  }
  return ActionDirection::UNKNOWN;
}

#endif  // ACTIONS_ACTION_DIRECTION_H_

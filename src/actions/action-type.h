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
#ifndef ACTIONS_ACTION_TYPE_H_
#define ACTIONS_ACTION_TYPE_H_

#include <string>

enum class ActionType {
  NOT_SUPPORTED,
  MAXIMIZE_RESTORE_WINDOW,
  FULLSCREEN_WINDOW,
  MINIMIZE_WINDOW,
  TILE_WINDOW,
  CLOSE_WINDOW,
  CHANGE_DESKTOP,
  SHOW_DESKTOP,
  SEND_KEYS,
  RUN_COMMAND,
  MOUSE_CLICK,
  // Adding a new action? Don't forget to add it in actionTypeToStr,
  // actionTypeFromStr and ActionFactory::buildAction
};

inline std::string actionTypeToStr(ActionType actionType) {
  switch (actionType) {
    case ActionType::MAXIMIZE_RESTORE_WINDOW:
      return "MAXIMIZE_RESTORE_WINDOW";
    case ActionType::FULLSCREEN_WINDOW:
      return "FULLSCREEN_WINDOW";
    case ActionType::MINIMIZE_WINDOW:
      return "MINIMIZE_WINDOW";
    case ActionType::TILE_WINDOW:
      return "TILE_WINDOW";
    case ActionType::CLOSE_WINDOW:
      return "CLOSE_WINDOW";
    case ActionType::CHANGE_DESKTOP:
      return "CHANGE_DESKTOP";
    case ActionType::SHOW_DESKTOP:
      return "SHOW_DESKTOP";
    case ActionType::SEND_KEYS:
      return "SEND_KEYS";
    case ActionType::RUN_COMMAND:
      return "RUN_COMMAND";
    case ActionType::MOUSE_CLICK:
      return "MOUSE_CLICK";
    default:
      return "NOT_SUPPORTED";
  }
}

inline ActionType actionTypeFromStr(const std::string &str) {
  if (str == "MAXIMIZE_RESTORE_WINDOW") {
    return ActionType::MAXIMIZE_RESTORE_WINDOW;
  }
  if (str == "FULLSCREEN_WINDOW") {
    return ActionType::FULLSCREEN_WINDOW;
  }
  if (str == "MINIMIZE_WINDOW") {
    return ActionType::MINIMIZE_WINDOW;
  }
  if (str == "TILE_WINDOW") {
    return ActionType::TILE_WINDOW;
  }
  if (str == "CLOSE_WINDOW") {
    return ActionType::CLOSE_WINDOW;
  }
  if (str == "CHANGE_DESKTOP") {
    return ActionType::CHANGE_DESKTOP;
  }
  if (str == "SHOW_DESKTOP") {
    return ActionType::SHOW_DESKTOP;
  }
  if (str == "SEND_KEYS") {
    return ActionType::SEND_KEYS;
  }
  if (str == "RUN_COMMAND") {
    return ActionType::RUN_COMMAND;
  }
  if (str == "MOUSE_CLICK") {
    return ActionType::MOUSE_CLICK;
  }
  return ActionType::NOT_SUPPORTED;
}

#endif  // ACTIONS_ACTION_TYPE_H_

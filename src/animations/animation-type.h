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
#ifndef ANIMATIONS_ANIMATION_TYPE_H_
#define ANIMATIONS_ANIMATION_TYPE_H_

#include <string>

enum class AnimationType {
  NONE,
  CHANGE_DESKTOP_UP,
  CHANGE_DESKTOP_DOWN,
  CHANGE_DESKTOP_LEFT,
  CHANGE_DESKTOP_RIGHT,
  CLOSE_WINDOW,
  MAXIMIZE_WINDOW,
  MINIMIZE_WINDOW,
  RESTORE_WINDOW,
  SHOW_DESKTOP,
  EXIST_SHOW_DESKTOP,
  TILE_WINDOW_LEFT,
  TILE_WINDOW_RIGHT,
  // Adding a new animation? Don't forget to add it in animationTypeToStr,
  // animationTypeFromStr and AnimationFactory::buildAnimation
};

inline std::string animationTypeToStr(AnimationType animationType) {
  switch (animationType) {
    case AnimationType::CHANGE_DESKTOP_UP:
      return "CHANGE_DESKTOP_UP";
    case AnimationType::CHANGE_DESKTOP_DOWN:
      return "CHANGE_DESKTOP_DOWN";
    case AnimationType::CHANGE_DESKTOP_LEFT:
      return "CHANGE_DESKTOP_LEFT";
    case AnimationType::CHANGE_DESKTOP_RIGHT:
      return "CHANGE_DESKTOP_RIGHT";
    case AnimationType::CLOSE_WINDOW:
      return "CLOSE_WINDOW";
    case AnimationType::MAXIMIZE_WINDOW:
      return "MAXIMIZE_WINDOW";
    case AnimationType::MINIMIZE_WINDOW:
      return "MINIMIZE_WINDOW";
    case AnimationType::RESTORE_WINDOW:
      return "RESTORE_WINDOW";
    case AnimationType::SHOW_DESKTOP:
      return "SHOW_DESKTOP";
    case AnimationType::EXIST_SHOW_DESKTOP:
      return "EXIST_SHOW_DESKTOP";
    case AnimationType::TILE_WINDOW_LEFT:
      return "TILE_WINDOW_LEFT";
    case AnimationType::TILE_WINDOW_RIGHT:
      return "TILE_WINDOW_RIGHT";
    default:
      return "NONE";
  }
}

inline AnimationType animationTypeFromStr(const std::string &str) {
  if (str == "CHANGE_DESKTOP_UP") {
    return AnimationType::CHANGE_DESKTOP_UP;
  }
  if (str == "CHANGE_DESKTOP_DOWN") {
    return AnimationType::CHANGE_DESKTOP_DOWN;
  }
  if (str == "CHANGE_DESKTOP_LEFT") {
    return AnimationType::CHANGE_DESKTOP_LEFT;
  }
  if (str == "CHANGE_DESKTOP_RIGHT") {
    return AnimationType::CHANGE_DESKTOP_RIGHT;
  }
  if (str == "CLOSE_WINDOW") {
    return AnimationType::CLOSE_WINDOW;
  }
  if (str == "MAXIMIZE_WINDOW") {
    return AnimationType::MAXIMIZE_WINDOW;
  }
  if (str == "MINIMIZE_WINDOW") {
    return AnimationType::MINIMIZE_WINDOW;
  }
  if (str == "RESTORE_WINDOW") {
    return AnimationType::RESTORE_WINDOW;
  }
  if (str == "SHOW_DESKTOP") {
    return AnimationType::SHOW_DESKTOP;
  }
  if (str == "EXIST_SHOW_DESKTOP") {
    return AnimationType::EXIST_SHOW_DESKTOP;
  }
  if (str == "TILE_WINDOW_LEFT") {
    return AnimationType::TILE_WINDOW_LEFT;
  }
  if (str == "TILE_WINDOW_RIGHT") {
    return AnimationType::TILE_WINDOW_RIGHT;
  }
  return AnimationType::NONE;
}

#endif  // ANIMATIONS_ANIMATION_TYPE_H_

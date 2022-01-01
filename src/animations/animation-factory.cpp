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
#include "animations/animation-factory.h"

#include <utility>

#include "actions/action-direction.h"
#include "animations/animation.h"
#include "animations/change-desktop-animation.h"
#include "animations/close-window-animation.h"
#include "animations/maximize-window-animation.h"
#include "animations/minimize-window-animation.h"
#include "animations/restore-window-animation.h"
#include "animations/show-desktop-animation.h"
#include "animations/tile-window-animation.h"

std::unique_ptr<Animation> AnimationFactory::buildAnimation(
    AnimationType type, const WindowSystem &windowSystem, const WindowT &window,
    Color color, Color borderColor) {
  switch (type) {
    case AnimationType::CHANGE_DESKTOP_UP:
      return std::make_unique<ChangeDesktopAnimation>(
          windowSystem, window, color, borderColor, ActionDirection::UP);
    case AnimationType::CHANGE_DESKTOP_DOWN:
      return std::make_unique<ChangeDesktopAnimation>(
          windowSystem, window, color, borderColor, ActionDirection::DOWN);
    case AnimationType::CHANGE_DESKTOP_LEFT:
      return std::make_unique<ChangeDesktopAnimation>(
          windowSystem, window, color, borderColor, ActionDirection::LEFT);
    case AnimationType::CHANGE_DESKTOP_RIGHT:
      return std::make_unique<ChangeDesktopAnimation>(
          windowSystem, window, color, borderColor, ActionDirection::RIGHT);
    case AnimationType::CLOSE_WINDOW:
      return std::make_unique<CloseWindowAnimation>(windowSystem, window, color,
                                                    borderColor);
    case AnimationType::MAXIMIZE_WINDOW:
      return std::make_unique<MaximizeWindowAnimation>(windowSystem, window,
                                                       color, borderColor);
    case AnimationType::MINIMIZE_WINDOW:
      return std::make_unique<MinimizeWindowAnimation>(windowSystem, window,
                                                       color, borderColor);
    case AnimationType::RESTORE_WINDOW:
      return std::make_unique<RestoreWindowAnimation>(windowSystem, window,
                                                      color, borderColor);
    case AnimationType::SHOW_DESKTOP:
      return std::make_unique<ShowDesktopAnimation>(windowSystem, window, color,
                                                    borderColor, false);
    case AnimationType::EXIST_SHOW_DESKTOP:
      return std::make_unique<ShowDesktopAnimation>(windowSystem, window, color,
                                                    borderColor, true);
    case AnimationType::TILE_WINDOW_LEFT:
      return std::make_unique<TileWindowAnimation>(windowSystem, window, color,
                                                   borderColor, true);
    case AnimationType::TILE_WINDOW_RIGHT:
      return std::make_unique<TileWindowAnimation>(windowSystem, window, color,
                                                   borderColor, false);
    default:
      return nullptr;
  }
}

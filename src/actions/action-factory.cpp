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
#include "actions/action-factory.h"

#include <utility>

#include "actions/action.h"
#include "actions/maximize-restore-window.h"
#include "actions/minimize-window.h"
#include "actions/tile-window.h"

std::unique_ptr<Action> ActionFactory::buildAction(
    ActionType type, std::unordered_map<std::string, std::string> settings,
    const WindowSystem &windowSystem, const WindowT &window,
    const Config &config) {
  switch (type) {
    case ActionType::MAXIMIZE_RESTORE_WINDOW:
      return std::make_unique<MaximizeRestoreWindow>(
          std::move(settings), windowSystem, window, config);
    case ActionType::MINIMIZE_WINDOW:
      return std::make_unique<MinimizeWindow>(std::move(settings), windowSystem,
                                              window, config);
    case ActionType::TILE_WINDOW:
      return std::make_unique<TileWindow>(std::move(settings), windowSystem,
                                          window, config);
    default:
      return nullptr;
  }
}

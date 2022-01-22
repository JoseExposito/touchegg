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
#include "actions/action-factory.h"

#include <utility>

#include "actions/action.h"
#include "actions/change-desktop.h"
#include "actions/close-window.h"
#include "actions/fullscreen-window.h"
#include "actions/maximize-restore-window.h"
#include "actions/minimize-window.h"
#include "actions/mouse-click.h"
#include "actions/run-command.h"
#include "actions/send-keys.h"
#include "actions/show-desktop.h"
#include "actions/tile-window.h"

std::unique_ptr<Action> ActionFactory::buildAction(
    ActionType type, std::unordered_map<std::string, std::string> settings,
    const WindowSystem &windowSystem, const WindowT &window,
    const Config &config) {
  switch (type) {
    case ActionType::MAXIMIZE_RESTORE_WINDOW:
      return std::make_unique<MaximizeRestoreWindow>(
          std::move(settings), windowSystem, window, config);
    case ActionType::FULLSCREEN_WINDOW:
      return std::make_unique<FullscreenWindow>(std::move(settings),
                                                windowSystem, window, config);
    case ActionType::MINIMIZE_WINDOW:
      return std::make_unique<MinimizeWindow>(std::move(settings), windowSystem,
                                              window, config);
    case ActionType::TILE_WINDOW:
      return std::make_unique<TileWindow>(std::move(settings), windowSystem,
                                          window, config);
    case ActionType::CLOSE_WINDOW:
      return std::make_unique<CloseWindow>(std::move(settings), windowSystem,
                                           window, config);
    case ActionType::CHANGE_DESKTOP:
      return std::make_unique<ChangeDesktop>(std::move(settings), windowSystem,
                                             window, config);
    case ActionType::SHOW_DESKTOP:
      return std::make_unique<ShowDesktop>(std::move(settings), windowSystem,
                                           window, config);
    case ActionType::SEND_KEYS:
      return std::make_unique<SendKeys>(std::move(settings), windowSystem,
                                        window, config);
    case ActionType::RUN_COMMAND:
      return std::make_unique<RunCommand>(std::move(settings), windowSystem,
                                          window, config);
    case ActionType::MOUSE_CLICK:
      return std::make_unique<MouseClick>(std::move(settings), windowSystem,
                                          window, config);
    default:
      return nullptr;
  }
}

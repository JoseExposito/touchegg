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
#ifndef ACTIONS_ACTION_H_
#define ACTIONS_ACTION_H_

#include <string>
#include <unordered_map>
#include <utility>

#include "config/config.h"
#include "gesture/gesture.h"
#include "window-system/window-system.h"

/**
 * Base class for all actions. Use the ActionFactory to build actions.
 */
class Action {
 public:
  /**
   * Default constructor.
   * @param settings Action settings.
   * @param windowSystem Object to access the underlaying window system.
   * @param window The window the gesture is performed on.
   * @param config Configuration.
   */
  Action(std::unordered_map<std::string, std::string> settings,
         const WindowSystem &windowSystem, const WindowT &window,
         const Config &config)
      : settings(std::move(settings)),
        windowSystem(windowSystem),
        window(window),
        config(config),
        threshold(Action::readThreshold(config)) {}
  virtual ~Action() = default;

  /**
   * The action must return a bool indicating if it can be executed in system
   * windows (dock, panel, desktop, etc).
   */
  virtual bool runOnSystemWindows() = 0;

  virtual void onGestureBegin(const Gesture &gesture) = 0;
  virtual void onGestureUpdate(const Gesture &gesture) = 0;
  virtual void onGestureEnd(const Gesture &gesture) = 0;

 protected:
  std::unordered_map<std::string, std::string> settings;
  const WindowSystem &windowSystem;
  const WindowT &window;
  const Config &config;
  /**
   * Special config value: threshold to execute action. All derived actions
   * must respect this.
   */
  const int threshold;

 private:
  /**
   * Fail-safe read gesture threshold property from config.
   * @param config Config to read threshold value from.
   * @returns action_execute_threshold.
   */
  static int readThreshold(const Config &config);
};

#endif  // ACTIONS_ACTION_H_

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

#ifndef ACTIONS_SCRIPT_H
#define ACTIONS_SCRIPT_H

#include <config/config.h>

#include <string>

#include "action-direction.h"

class Script {
 public:
  /**
   * Initialise the script object to allow a script to implement actions
   * @param path the path to the script file
   */
  explicit Script(const std::string& path);
  virtual ~Script() = default;
  void CallGestureStartFn(std::unordered_map<std::string, std::string> settings,
                          const Config &config);
  void CallAnimateFn(double percentage);
  void CallGestureEndFn(ActionDirection direction);

  static Script loadScript(const std::string& path);
};

#endif  // ACTIONS_SCRIPT_H

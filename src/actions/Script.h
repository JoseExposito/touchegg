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

#include <functional>
#include <string>

#include "action-direction.h"

using GestureStart = void (*)(std::unordered_map<std::string, std::string>, const Config &);
using Animate = void (*)(double);
using GestureEnd = void (*)(ActionDirection);

class Script {
 public:
  /**
   * Initialise the script object to allow a script to implement actions
   * @param path the path to the script file
   */
  explicit Script(const std::string& path);
  virtual ~Script() = default;

  void gesture_start(std::unordered_map<std::string, std::string>, const Config &);
  void animate(double percentage);
  void gesture_end(ActionDirection);

 private:
  void* lib;

  GestureStart gesture_start_fn;
  Animate animate_fn;
  GestureEnd gesture_end_fn;

//    void gesture_start(std::unordered_map<std::string, std::string> settings,
//                            const Config &config);
//    void animate(double percentage);
//    void gesture_end(ActionDirection direction);
};

#endif  // ACTIONS_SCRIPT_H

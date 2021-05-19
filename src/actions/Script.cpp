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

#include "Script.h"

#include <iostream>
#include <utility>

Script::Script(const std::string& path) {
  std::cout << "Initialising script from " << path << std::endl;
}

void Script::CallGestureStartFn(
    std::unordered_map<std::string, std::string> settings,
    const Config &config) {

  std::cout << "Calling Script" << std::endl;
}

void Script::CallAnimateFn(double percentage) {
  std::cout << "Animating - " << percentage * 100 << "%" << std::endl;
}

void Script::CallGestureEndFn(ActionDirection direction) {
  std::cout << "End Gesture" << std::endl;
}

Script Script::loadScript(const std::string& path) {
  Script src(path);

  return src;
}

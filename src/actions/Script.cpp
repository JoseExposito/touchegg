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

#include <dlfcn.h>

#include <iostream>
#include <utility>

Script::Script(const std::string& path) : lib(dlopen(path.c_str(), RTLD_NOW)) {
  if (lib == nullptr) {
    throw std::invalid_argument("Unable to locate script.");
  }

  this->gesture_start_fn = *(GestureStart)(dlsym(lib, "gesture_start"));
  this->animate_fn = *(Animate)(dlsym(lib, "animate"));
  this->gesture_end_fn = *(GestureEnd)(dlsym(lib, "gesture_end"));
}

void Script::gesture_start(std::unordered_map<std::string, std::string> settings, const Config &config) {
  this->gesture_start_fn(std::move(settings), config);
}

void Script::animate(double percentage) {
  this->animate_fn(percentage);
}

void Script::gesture_end(ActionDirection direction) {
  this->gesture_end_fn(direction);
  dlclose(this->lib);
}
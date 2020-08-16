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
#include "utils/split.h"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> split(const std::string &string, char delimiter) {
  std::stringstream ss(string);
  std::string item;
  std::vector<std::string> elems;

  while (std::getline(ss, item, delimiter)) {
    elems.push_back(std::move(item));
  }

  return elems;
}

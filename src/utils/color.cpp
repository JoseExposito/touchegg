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
#include "utils/color.h"

#include <iostream>

Color::Color(const std::string &hexString) {
  if (hexString.size() != 6 &&
      (hexString.size() != 7 && hexString.front() != '#')) {
    return;
  }

  size_t offset = (hexString.size() == 6) ? 0 : 1;
  this->red = std::stoi(hexString.substr(offset, 2), nullptr, 16);
  this->green = std::stoi(hexString.substr(offset + 2, 2), nullptr, 16);
  this->blue = std::stoi(hexString.substr(offset + 4, 2), nullptr, 16);
}

double Color::r() const { return this->red / 255.0; }

double Color::g() const { return this->green / 255.0; }

double Color::b() const { return this->blue / 255.0; }

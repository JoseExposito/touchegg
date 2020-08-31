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
#ifndef UTILS_COLOR_H_
#define UTILS_COLOR_H_

#include <string>

/**
 * Simple class to parse color from config and use them with Cairo.
 */
class Color {
 public:
  Color() = default;

  /**
   * @param hexString A string like "RRGGBB" or "#RRGGBB".
   */
  explicit Color(const std::string &hexString);

  double r() const;
  double g() const;
  double b() const;

 private:
  double red = 62.0;
  double green = 159.0;
  double blue = 237.0;
};

#endif  // UTILS_COLOR_H_

/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
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
#ifndef UTILS_COLOR_H_
#define UTILS_COLOR_H_

#include <string>

enum class ColorType {
  BACKGROUND,
  BORDER,
};

/**
 * Simple class to parse color from config and use them with Cairo.
 */
class Color {
 public:
  Color() = default;

  /**
   * @param hexString A string like "RRGGBB", "#RRGGBB" or "auto".
   */
  Color(const std::string &hexString, ColorType colorType);

  double r() const { return this->red; }
  double g() const { return this->green; }
  double b() const { return this->blue; }

 private:
  double red = 0.6;
  double green = 0.6;
  double blue = 0.6;

  void setFromHexString(const std::string &hexString);
  void setFromAutoColor(ColorType colorType);
};

#endif  // UTILS_COLOR_H_

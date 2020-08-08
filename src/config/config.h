/**
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
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2020
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <string>

class Config {
 public:
  void loadConfig();

 private:
  /**
   * Returns the path of the user's home directory.
   * @return User's home directory.
   */
  static std::filesystem::path getHomePath();
};

#endif /* CONFIG_H */

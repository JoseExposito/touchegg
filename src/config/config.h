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
#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include <filesystem>
#include <string>
#include <unordered_map>

class Config {
 public:
  Config();

 private:
  /**
   * Configuration is saved here to ensure 0(1) access.
   * Key: [Application].[GestureType].[NumFingers].[Direction].[action/settings]
   * Value: Action or settings associated with the gesture
   */
  std::unordered_map<std::string, std::string> config;

  /**
   * Parse the configuration placed on the user's home directory
   */
  void parseConfig();

  /**
   * Check that the required configuration files are in place.
   */
  static void copyConfingIfNotPresent();

  /**
   * Return the path of the user's home directory.
   * @return User's home directory.
   */
  static std::filesystem::path getHomePath();
};

#endif /* CONFIG_CONFIG_H_ */

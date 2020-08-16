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
#ifndef CONFIG_XML_CONFIG_LOADER_H_
#define CONFIG_XML_CONFIG_LOADER_H_

#include "utils/filesystem.h"
class Config;

/**
 * Default config loader. It reads the configuration from
 * "~/.config/touchegg/touchegg.conf" and stores it in `Config`.
 * @see Config
 */
class XmlConfigLoader {
 public:
  /**
   * Default contructor, it takes a reference to the `Config` object where the
   * configuration will be stored.
   * @param config A mutable reference to the `Config` object.
   */
  explicit XmlConfigLoader(Config *config);

  /**
   * Store the configuration from the XML configuration file in the `Config`
   * object passed in the constructor.
   */
  void load();

 private:
  /**
   * Reference to the `Config` object injected in the constructor.
   */
  Config *config;

  /**
   * Parse the XML configuration file placed in path.
   * @param configPath Path to the configuration file.
   */
  void parseXml(const std::filesystem::path &configPath);

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

#endif  // CONFIG_XML_CONFIG_LOADER_H_

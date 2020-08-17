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

#include <string>
#include <unordered_map>

/**
 * Class to save and access the configuration.
 * It only provides a simple interface to get/set the configuration, delegating
 * the responsability of saving the configuration to a third party, usually
 * `XmlConfigLoader`.
 */
class Config {
 public:
  /**
   * Save the settings associated to a gesture.
   */
  void saveGestureConfig(
      const std::string &application, const std::string &gesture,
      const std::string &numFingers, const std::string &direction,
      const std::string &action,
      std::unordered_map<std::string, std::string> actionSettings);

  /**
   * Remove all saved settings.
   */
  inline void clear() { this->config.clear(); }

 private:
  /**
   * Configuration is saved here to ensure 0(1) access.
   * Key: [Application]_[GestureType]_[NumFingers]_[Direction].
   * Value: Action and settings associated with the gesture.
   */
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
      config;
};

#endif /* CONFIG_CONFIG_H_ */

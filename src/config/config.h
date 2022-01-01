/**
 * Copyright 2011 - 2022 José Expósito <jose.exposito89@gmail.com>
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
#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include <string>
#include <unordered_map>
#include <utility>

#include "actions/action-type.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"

/**
 * Class to save and access the configuration.
 * It only provides a simple interface to get/set the configuration, delegating
 * the responsability of saving the configuration to a third party, usually
 * `XmlConfigLoader`.
 */
class Config {
 public:
  Config();

  /**
   * Remove all saved settings.
   */
  void clear();

  /**
   * Save a global setting.
   * @param name Setting name, for example "threshold".
   * @param value Setting value, for example "1000".
   */
  void saveGlobalSetting(const std::string &name, const std::string &value);

  /**
   * @returns If the global setting is set.
   */
  bool hasGlobalSetting(const std::string &name) const;

  /**
   * Return a global settings value.
   * @param Setting name, for example "threshold".
   * @returns Setting value, for example "1000".
   */
  std::string getGlobalSetting(const std::string &name) const;

  /**
   * Save the settings associated to a gesture.
   */
  void saveGestureConfig(
      const std::string &application, GestureType gestureType,
      const std::string &numFingers, GestureDirection gestureDirection,
      ActionType actionType,
      const std::unordered_map<std::string, std::string> &actionSettings);

  /**
   * @returns If there is an action configured for the gesture.
   */
  bool hasGestureConfig(const std::string &application, GestureType gestureType,
                        int numFingers,
                        GestureDirection gestureDirection) const;

  /**
   * @returns The action configured for the gesture.
   */
  std::pair<ActionType, std::unordered_map<std::string, std::string>>
  getGestureConfig(const std::string &application, GestureType gestureType,
                   int numFingers, GestureDirection gestureDirection) const;

 private:
  /**
   * Global settings are stored here to ensure 0(1) access.
   * Key: Global settings name.
   * Value: Global setting value.
   */
  std::unordered_map<std::string, std::string> globalSettings;

  /**
   * Configuration is saved here to ensure 0(1) access.
   * Key: As returned from Config::getConfigKey.
   * Value: Action type and settings associated with it.
   */
  std::unordered_map<
      std::string,
      std::pair<ActionType, std::unordered_map<std::string, std::string>>>
      config;

  /**
   * Load the default global settings.
   */
  void loadDefaultGlobalSettings();

  /**
   * Return a key that can be use to get/set a gesture configuration value
   * from/in "config".
   */
  static std::string getConfigKey(const std::string &application,
                                  GestureType gestureType,
                                  const std::string &numFingers,
                                  GestureDirection gestureDirection);
};

#endif  // CONFIG_CONFIG_H_

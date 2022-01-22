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
#include "config/config.h"

#include <string>
#include <unordered_map>

#include "utils/string.h"

Config::Config() { this->loadDefaultGlobalSettings(); }

void Config::clear() {
  this->globalSettings.clear();
  this->config.clear();
  this->loadDefaultGlobalSettings();
}

void Config::saveGlobalSetting(const std::string &name,
                               const std::string &value) {
  this->globalSettings[name] = value;
}

bool Config::hasGlobalSetting(const std::string &name) const {
  return (this->globalSettings.count(name) == 1);
}

std::string Config::getGlobalSetting(const std::string &name) const {
  return this->globalSettings.at(name);
}

void Config::saveGestureConfig(
    const std::string &application, GestureType gestureType,
    const std::string &numFingers, GestureDirection gestureDirection,
    ActionType actionType,
    const std::unordered_map<std::string, std::string> &actionSettings) {
  std::string key = Config::getConfigKey(application, gestureType, numFingers,
                                         gestureDirection);
  this->config[key] = std::make_pair(actionType, actionSettings);
}

bool Config::hasGestureConfig(const std::string &application,
                              GestureType gestureType, int numFingers,
                              GestureDirection gestureDirection) const {
  std::string key = Config::getConfigKey(
      application, gestureType, std::to_string(numFingers), gestureDirection);
  return (this->config.count(key) == 1);
}

std::pair<ActionType, std::unordered_map<std::string, std::string>>
Config::getGestureConfig(const std::string &application,
                         GestureType gestureType, int numFingers,
                         GestureDirection gestureDirection) const {
  std::string key = Config::getConfigKey(
      application, gestureType, std::to_string(numFingers), gestureDirection);
  return this->config.at(key);
}

void Config::loadDefaultGlobalSettings() {
  this->globalSettings["animation_delay"] = "150";
  this->globalSettings["action_execute_threshold"] = "20";
}

std::string Config::getConfigKey(const std::string &application,
                                 GestureType gestureType,
                                 const std::string &numFingers,
                                 GestureDirection gestureDirection) {
  auto gestureTypeInt = static_cast<int>(gestureType);
  auto gestureDirectionInt = static_cast<int>(gestureDirection);
  return toLower(application) + "_" + std::to_string(gestureTypeInt) + "_" +
         numFingers + "_" + std::to_string(gestureDirectionInt);
}

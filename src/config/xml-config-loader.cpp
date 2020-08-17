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
#include "config/xml-config-loader.h"

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "config/config.h"
#include "pugixml/pugixml.hpp"
#include "utils/filesystem.h"
#include "utils/split.h"

namespace {
const char *USR_SHARE_CONFIG_DIR = "/usr/share/touchegg";
const char *HOME_CONFIG_DIR = ".config/touchegg";
const char *CONFIG_FILE = "touchegg.conf";
}  // namespace

XmlConfigLoader::XmlConfigLoader(Config *config) : config(config) {
  XmlConfigLoader::copyConfingIfNotPresent();
}

void XmlConfigLoader::load() {
  const std::filesystem::path homePath = XmlConfigLoader::getHomePath();
  const std::filesystem::path configPath =
      homePath / HOME_CONFIG_DIR / CONFIG_FILE;

  this->parseXml(configPath);
}

void XmlConfigLoader::parseXml(const std::filesystem::path &configPath) {
  pugi::xml_document doc;
  pugi::xml_parse_result parsedSuccessfully = doc.load_file(configPath.c_str());

  if (!parsedSuccessfully) {
    throw std::runtime_error{"Error parsing configuration file"};
  }

  pugi::xml_node rootNode = doc.document_element();
  this->parseApplicationXmlNodes(rootNode);
}

void XmlConfigLoader::parseApplicationXmlNodes(const pugi::xml_node &rootNode) {
  for (pugi::xml_node applicationNode : rootNode.children("application")) {
    const std::string appsStr = applicationNode.attribute("name").value();
    const std::vector<std::string> applications = split(appsStr, ',');

    for (pugi::xml_node gestureNode : applicationNode.children("gesture")) {
      const std::string gestureType = gestureNode.attribute("type").value();
      const std::string fingers = gestureNode.attribute("fingers").value();
      const std::string direction = gestureNode.attribute("direction").value();

      pugi::xml_node actionNode = gestureNode.child("action");
      const std::string actionType = actionNode.attribute("type").value();

      std::unordered_map<std::string, std::string> actionSettings;
      for (pugi::xml_node settingNode : actionNode.children()) {
        const std::string settingName = settingNode.name();
        const std::string settingValue = settingNode.child_value();
        actionSettings[settingName] = settingValue;
      }

      // Save the gesture config for each application
      for (const std::string &application : applications) {
        this->config->saveGestureConfig(application, gestureType, fingers,
                                        direction, actionType, actionSettings);
      }
    }
  }
}

void XmlConfigLoader::copyConfingIfNotPresent() {
  const std::filesystem::path homePath = XmlConfigLoader::getHomePath();
  const std::filesystem::path homeConfigDir = homePath / HOME_CONFIG_DIR;
  const std::filesystem::path homeConfigFile = homeConfigDir / CONFIG_FILE;

  // If the ~/.config/touchegg configuration file exists we can continue,
  // otherwise we need to copy it from /usr/share/touchegg/touchegg.conf
  if (std::filesystem::exists(homeConfigFile)) {
    return;
  }

  const std::filesystem::path usrConfigDir{USR_SHARE_CONFIG_DIR};
  const std::filesystem::path usrConfigFile{usrConfigDir / CONFIG_FILE};
  if (!std::filesystem::exists(usrConfigFile)) {
    throw std::runtime_error{
        "File /usr/share/touchegg/touchegg.conf not found.\n"
        "Reinstall Touchégg to solve this issue"};
  }

  std::filesystem::create_directories(homeConfigDir);
  std::filesystem::copy_file(usrConfigFile, homeConfigFile);
}

std::filesystem::path XmlConfigLoader::getHomePath() {
  // $HOME should be checked first
  const char *homeEnvVar = getenv("HOME");
  if (homeEnvVar != nullptr) {
    return std::filesystem::path{homeEnvVar};
  }

  // In case $HOME is not set fallback to getpwuid
  const struct passwd *userInfo = getpwuid(getuid());  // NOLINT
  if (userInfo == nullptr) {
    throw std::runtime_error{
        "Error getting your home directory path (getpwuid).\n"
        "Please file a bug report at "
        "https://github.com/JoseExposito/touchegg/issues"};
  }

  const char *workingDir = userInfo->pw_dir;
  if (workingDir == nullptr) {
    throw std::runtime_error{
        "Error getting your home directory path (pw_dir).\n"
        "Please file a bug report at "
        "https://github.com/JoseExposito/touchegg/issues"};
  }

  return std::filesystem::path{workingDir};
}

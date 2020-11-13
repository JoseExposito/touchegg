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
#include "config/xml-config-loader.h"

#include <sys/inotify.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <chrono>  // NOLINT
#include <cstdlib>
#include <exception>
#include <iostream>
#include <pugixml.hpp>  // NOLINT
#include <stdexcept>
#include <string>
#include <thread>  // NOLINT
#include <unordered_map>
#include <utility>
#include <vector>

#include "config/config.h"
#include "utils/filesystem.h"
#include "utils/paths.h"
#include "utils/string.h"

namespace {
constexpr std::size_t WATCH_EVENT_SIZE = sizeof(struct inotify_event);
constexpr std::size_t WATCH_BUFFER_SIZE = (100 * (WATCH_EVENT_SIZE + 16));
}  // namespace

XmlConfigLoader::XmlConfigLoader(Config *config) : config(config) {}

void XmlConfigLoader::load() {
  const std::filesystem::path usrConfigFile = Paths::getSystemConfigFilePath();
  const std::filesystem::path homeConfigFile = Paths::getUserConfigFilePath();

  if (!std::filesystem::exists(usrConfigFile)) {
    throw std::runtime_error{
        "File /usr/share/touchegg/touchegg.conf not found.\n"
        "Reinstall Touchégg to solve this issue"};
  }

  const std::filesystem::path configPath =
      std::filesystem::exists(homeConfigFile) ? homeConfigFile : usrConfigFile;
  std::cout << "Using configuration file " << configPath << std::endl;
  this->parseXml(configPath);
  this->watchFile(configPath);
}

void XmlConfigLoader::parseXml(const std::filesystem::path &configPath) {
  pugi::xml_document doc;
  pugi::xml_parse_result parsedSuccessfully = doc.load_file(configPath.c_str());

  if (!parsedSuccessfully) {
    throw std::runtime_error{"Error parsing configuration file"};
  }

  pugi::xml_node rootNode = doc.document_element();
  this->parseGlobalSettings(rootNode);
  this->parseApplicationXmlNodes(rootNode);
}

void XmlConfigLoader::parseGlobalSettings(const pugi::xml_node &rootNode) {
  pugi::xml_node settingsNode = rootNode.child("settings");
  for (pugi::xml_node propertyNode : settingsNode.children("property")) {
    const std::string property = propertyNode.attribute("name").value();
    const std::string value = propertyNode.child_value();
    this->config->saveGlobalSetting(property, value);
  }
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
        this->config->saveGestureConfig(
            trim(application), gestureTypeFromStr(gestureType), fingers,
            gestureDirectionFromStr(direction), actionTypeFromStr(actionType),
            actionSettings);
      }
    }
  }
}

void XmlConfigLoader::watchFile(const std::filesystem::path &configPath) {
  // https://developer.ibm.com/tutorials/l-ubuntu-inotify/
  const std::string warningMessage =
      "It was not posssible to monitor your configuration file for changes. "
      "Touchégg will not be able to automatically reload your configuration "
      "when you change it. You will need to restart Touchégg to apply your "
      "configuration changes";

  int fd = inotify_init();
  if (fd < 0) {
    std::cout << warningMessage << std::endl;
    return;
  }

  int wd = inotify_add_watch(fd, configPath.c_str(), IN_MODIFY | IN_CREATE);
  if (wd < 0) {
    std::cout << warningMessage << std::endl;
    return;
  }

  std::thread watchThread{[fd, configPath, this]() {
    std::array<char, WATCH_BUFFER_SIZE> buffer{};
    while (true) {
      bool reloadSettings = false;
      bool allEventsRead = false;

      while (!allEventsRead) {
        const std::size_t length = read(fd, buffer.data(), buffer.size());

        std::this_thread::sleep_for(std::chrono::seconds(1));

        unsigned int available = 0;
        ioctl(fd, FIONREAD, &available);  // NOLINT

        reloadSettings = (length > 0);
        allEventsRead = (available <= 0);
      }

      if (reloadSettings) {
        std::cout << "Your configuration file changed, reloading your settings"
                  << std::endl;
        this->config->clear();
        this->parseXml(configPath);
      }
    }
  }};
  watchThread.detach();
}

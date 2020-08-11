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
#include "config/config.h"

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <exception>
#include <filesystem>  // NOLINT
#include <string>
#include <vector>

namespace {
const char *USR_SHARE_CONFIG_DIR = "/usr/share/touchegg";
const char *HOME_CONFIG_DIR = ".config/touchegg";
const char *CONFIG_FILE = "touchegg.conf";
}  // namespace

Config::Config() {
  Config::copyConfingIfNotPresent();
  this->parseConfig();
}

void Config::parseConfig() {
  const std::filesystem::path homePath = Config::getHomePath();
  const std::filesystem::path configPath =
      homePath / HOME_CONFIG_DIR / CONFIG_FILE;

  // TODO(jose) Test
  this->config["foo"] = "bar";
}

void Config::copyConfingIfNotPresent() {
  const std::filesystem::path homePath = Config::getHomePath();
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

std::filesystem::path Config::getHomePath() {
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

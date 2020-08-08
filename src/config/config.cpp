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
#include "config.h"

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <exception>
#include <filesystem>
#include <string>
#include <vector>

namespace {
const char *USR_SHARE_CONFIG_FILE = "/usr/share/touchegg/touchegg.conf";
const char *HOME_CONFIG_FILE = "/.config/touchegg/touchegg.conf";
const char *HOME_CONFIG_DIR = ".config/touchegg";
}  // namespace

void Config::loadConfig() {
  const std::filesystem::path usrFile{USR_SHARE_CONFIG_FILE};

  if (!std::filesystem::exists(usrFile)) {
    throw std::runtime_error{
        "File " + USR_SHARE_CONFIG_FILE +
        " not found. Reinstall Touchégg to solve this issue"};
  }

  const std::filesystem::path homePath = Config::getHomePath();
}

std::filesystem::path Config::getHomePath() {
  // $HOME should be checked first
  const char *homeEnvVar = getenv("HOME");
  if (homeEnvVar != nullptr) {
    return std::filesystem::path{homeEnvVar};
  }

  // In case $HOME is not set fallback to getpwuid
  const struct passwd *userInfo = getpwuid(getuid());
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

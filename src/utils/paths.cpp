/**
 * Copyright 2011 - 2021 José Expósito <jose.exposito89@gmail.com>
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
#include "utils/paths.h"

#include <pwd.h>
#include <sys/inotify.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdexcept>

std::filesystem::path Paths::getHomePath() {
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

std::filesystem::path Paths::getUserConfigDirPath() {
  std::filesystem::path homePath = Paths::getHomePath();
  return std::filesystem::path{homePath / ".config" / "touchegg"};
}

std::filesystem::path Paths::getUserConfigFilePath() {
  std::filesystem::path configPath = Paths::getUserConfigDirPath();
  return std::filesystem::path{configPath / "touchegg.conf"};
}

std::filesystem::path Paths::getUserLockFilePath() {
  std::filesystem::path configPath = Paths::getUserConfigDirPath();
  return std::filesystem::path{configPath / ".touchegg.lock"};
}

std::filesystem::path Paths::getSystemConfigFilePath() {
  return std::filesystem::path{SYSTEM_CONFIG_FILE_PATH};
}

void Paths::createUserConfigDir() {
  std::filesystem::path homeConfigDir = Paths::getUserConfigDirPath();
  if (!std::filesystem::exists(homeConfigDir)) {
    std::filesystem::create_directories(homeConfigDir);
  }
}

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
#include "utils/paths.h"

#include <pwd.h>
#include <sys/inotify.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "utils/string.h"

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
  // If $XDG_CONFIG_HOME is set, use it. Otherwise fallback to $HOME/.config:
  // https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
  const char *xdgConfigHomeEnvVar = getenv("XDG_CONFIG_HOME");

  std::filesystem::path configPath =
      (xdgConfigHomeEnvVar != nullptr)
          ? std::filesystem::path{xdgConfigHomeEnvVar}
          : Paths::getHomePath() / ".config";

  return configPath / "touchegg";
}

std::filesystem::path Paths::getUserConfigFilePath() {
  std::filesystem::path configPath = Paths::getUserConfigDirPath();
  return std::filesystem::path{configPath / "touchegg.conf"};
}

std::filesystem::path Paths::getUserLockFilePath(
    const std::string &lockInstance) {
  std::filesystem::path configPath = Paths::getUserConfigDirPath();
  const std::string fileName = ".touchegg" + lockInstance + ".lock";
  return std::filesystem::path{configPath / fileName};
}

std::filesystem::path Paths::getSystemConfigFilePath() {
  // If $XDG_CONFIG_DIRS is set, check if the config is present in one of those
  // directories. Otherwise, fallback to /etc/xdg, as in the spec:
  // https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
  // Finally, fallback to SYSTEM_CONFIG_FILE_PATH for backwards compatibility.
  const char *xdgConfigDirsEnvVar = getenv("XDG_CONFIG_DIRS");
  std::vector<std::string> xdgPaths = (xdgConfigDirsEnvVar != nullptr)
                                          ? split(xdgConfigDirsEnvVar, ':')
                                          : std::vector<std::string>();
  xdgPaths.emplace_back("/etc/xdg");

  for (const std::string &path : xdgPaths) {
    std::filesystem::path configPath = std::filesystem::path{path};
    configPath = configPath / "touchegg" / "touchegg.conf";
    if (std::filesystem::exists(configPath)) {
      return configPath;
    }
  }

  return std::filesystem::path{SYSTEM_CONFIG_FILE_PATH};
}

void Paths::createUserConfigDir() {
  std::filesystem::path homeConfigDir = Paths::getUserConfigDirPath();
  if (!std::filesystem::exists(homeConfigDir)) {
    std::filesystem::create_directories(homeConfigDir);
  }
}

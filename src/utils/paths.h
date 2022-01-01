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
#ifndef UTILS_PATHS_H_
#define UTILS_PATHS_H_

#include <string>

#include "utils/filesystem.h"

/**
 * Utility class to get usefull paths.
 */
class Paths {
 public:
  /**
   * @return User's home directory path.
   */
  static std::filesystem::path getHomePath();

  /**
   * @return User's config directory path (~/.config/touchegg).
   */
  static std::filesystem::path getUserConfigDirPath();

  /**
   * @return User's config file path (~/.config/touchegg/touchegg.conf).
   */
  static std::filesystem::path getUserConfigFilePath();

  /**
   * @return User's lock file path
   * (~/.config/touchegg/.touchegg{lockInstance}.lock).
   */
  static std::filesystem::path getUserLockFilePath(
      const std::string &lockInstance);

  /**
   * @return System config file path (/usr/share/touchegg/touchegg.conf).
   */
  static std::filesystem::path getSystemConfigFilePath();

  /**
   * Creates the "getUserConfigDirPath" directory.
   */
  static void createUserConfigDir();
};

#endif  // UTILS_PATHS_H_

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

#include <string>
#include <unordered_map>

void Config::saveGestureConfig(
    const std::string &application, const std::string &gesture,
    const std::string &numFingers, const std::string &direction,
    const std::string &action,
    std::unordered_map<std::string, std::string> actionSettings) {
  // TODO(jose) Store NO_DIRECTION in a enum
  const std::string directionKey =
      direction.empty() ? "NO_DIRECTION" : direction;

  const std::string key =
      application + "_" + gesture + "_" + numFingers + "_" + directionKey;

  actionSettings["action"] = action;

  this->config[key] = actionSettings;
}

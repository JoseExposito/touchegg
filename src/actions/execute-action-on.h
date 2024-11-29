/**
 * Copyright 2011 - 2024 José Expósito <jose.exposito89@gmail.com>
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
#ifndef ACTIONS_EXECUTE_ACTION_ON_H_
#define ACTIONS_EXECUTE_ACTION_ON_H_

#include <string>

enum class ExecuteActionOn {
  NOT_SUPPORTED,
  BEGIN,
  END,
  // Adding a new value? Don't forget to add it in executeActionOnFromStr and
  // shouldExecuteAction
};

inline ExecuteActionOn executeActionOnFromStr(const std::string &str) {
  if (str == "begin") {
    return ExecuteActionOn::BEGIN;
  }
  if (str == "end") {
    return ExecuteActionOn::END;
  }
  return ExecuteActionOn::NOT_SUPPORTED;
}

inline bool shouldExecuteAction(ExecuteActionOn phase, ExecuteActionOn config) {
  switch (config) {
    case ExecuteActionOn::BEGIN:
      return phase == ExecuteActionOn::BEGIN;
    case ExecuteActionOn::END:
      return phase == ExecuteActionOn::END;
    default:
      return false;
  }
}

#endif  // ACTIONS_EXECUTE_ACTION_ON_H_

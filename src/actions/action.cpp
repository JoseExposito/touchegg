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
#include "actions/action.h"

#include <algorithm>

int Action::readThreshold(const Config &config) {
  int threshold = 0;
  try {
    threshold =
      std::stoi(config.getGlobalSetting("action_execute_threshold"));
  } catch (std::exception& e) {
    std::cout << "Bad action_execute_threshold value: "
              << e.what() << std::endl;
    // leave default 0 if numeric conversion failed
  }
  // discard negative percentage
  return std::max(threshold, 0);
}

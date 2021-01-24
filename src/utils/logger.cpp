/**
 * Copyright 2021 John Mifsud <imabuddha@gmail.com>
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

#include "utils/logger.h"

Logger::Logger() {
  uninitialized = true;

  // defaults
  logInfo = true;
  logWarning = true;
  logError = true;
  logDebug = false;
  logGestures = true;
  logGestureUpdates = true;
}

void Logger::Init(const bool verbose, const bool quiet, const bool noGestures,
                  const bool noUpdates) {
  uninitialized = false;

  // primary logging options
  if (quiet) {
    logInfo = false;
    logWarning = false;
    logError = false;
    logGestures = false;
    logGestureUpdates = false;
  } else if (verbose) {
    logDebug = true;
  }

  // special case options
  if (noGestures) {
    logGestures = false;
  }

  if (noUpdates) {
    logGestureUpdates = false;
  }
}

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
#include "logger.h"

#include <iostream>

namespace tlg {
LogLevel error = LogLevel::ERROR;
LogLevel warning = LogLevel::WARNING;
LogLevel info = LogLevel::INFO;
LogLevel debug = LogLevel::DEBUG;

LogLevel gesture = LogLevel::GESTURE_INFO;
LogLevel update = LogLevel::UPDATE_INFO;
}  // namespace tlg

bool Logger::Enabled(const LogLevel &lvl) {
  switch (lvl) {
    case LogLevel::INFO:
      return logInfo;
    case LogLevel::WARNING:
      return logWarning;
    case LogLevel::ERROR:
      return logError;
    case LogLevel::DEBUG:
      return logDebug;
    case LogLevel::GESTURE_INFO:
      return logGestures && logInfo;
    case LogLevel::UPDATE_INFO:
      return logGestureUpdates && logInfo;

    default:
      std::cerr << "Unknown LogLevel!" << std::endl;
      return false;
  }
}

std::ostream &Logger::GetStream(const LogLevel &lvl) {
  switch (lvl) {
    case LogLevel::ERROR:
      return std::cerr;

    default:
      return std::cout;
  }
}

/**
 * I hate that the following func isn't DRY, (the body repeats the template in
 * the class header), but I don't see any way around this. Just keep this in
 * mind if/when you modify the function: it should probably be the same in both
 * places.
 */
LogLevel operator<<(const LogLevel &lvl, std::ostream &(*msg)(std::ostream &)) {
  if (Logger::obj().Enabled(lvl)) {
    Logger::obj().GetStream(lvl) << msg;
  }

  return lvl;
}

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
    logGestureUpdates = false;
  }

  if (noUpdates) {
    logGestureUpdates = false;
  }
}

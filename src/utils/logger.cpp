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

#include <iostream>

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

// I hate that the following 2 funcs aren't DRY, but…
Logger::LogLevel operator<<(const Logger::LogLevel &lvl,
                            const std::string &msg) {
  if (Logger::obj().Enabled(lvl)) {
    Logger::obj().GetStream(lvl) << msg;
  }

  return lvl;
}
Logger::LogLevel operator<<(const Logger::LogLevel &lvl, const double &msg) {
  if (Logger::obj().Enabled(lvl)) {
    Logger::obj().GetStream(lvl) << msg;
  }

  return lvl;
}

Logger::LogLevel operator<<(const Logger::LogLevel &lvl,
                            std::ostream &(*msg)(std::ostream &)) {
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
  }

  if (noUpdates) {
    logGestureUpdates = false;
  }
}

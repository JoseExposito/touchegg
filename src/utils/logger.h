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
#ifndef UTILS_LOGGER_H_
#define UTILS_LOGGER_H_

#include <string>

// Logger::LogLevel operator<<(const LogLevel level, std::string &msg);
class Logger {
 public:
  enum class LogLevel { INFO, WARNING, ERROR, DEBUG };
};

/**
 * Singleton class to provide simple logging functionality.
 */
class LoggerOptions {
 public:
  /**
   * This static method controls the access to the singleton.
   * On first run,it creates a singleton object and places it into the
   * static member. On subsequent calls, it returns the existing obj.
   *
   * NOTE: Not thread safe! It's OK because it's called first in main.cpp.
   *
   * @return ptr to the Logger singleton
   */
  static LoggerOptions *Get(const bool verbose = false,
                            const bool quiet = false,
                            const bool noGesturequiet = false,
                            const bool noUpdatequiet = false);

  /**
   * @return true if the logger should be called for gesture msgs. Necessary
   * because the logging funcs don't know what kind of msg is being passed.
   */
  static bool logGestures() { return gestures; }

  /**
   * @return true if the logger should be called for gesture msgs. Necessary
   * because the logging funcs don't know what kind of msg is being passed.
   */
  static bool logGestureUpdates() { return updates; }

  // Should not be cloneable.
  LoggerOptions(const LoggerOptions &) = delete;

  // Should not be assignable.
  void operator=(const LoggerOptions &) = delete;

 protected:
  LoggerOptions(const bool verbose, const bool quiet, const bool noGestures,
                const bool noUpdates);

  static LoggerOptions *singleton_;

  // These indicate if the various logging levels should be enabled.
  static bool logInfo, logWarning, logError, logDebug;

  // If true then gesture msgs should be logged.
  static bool gestures;

  // If true then gesture update % msgs should be logged.
  static bool updates;
};

#endif  // UTILS_LOGGER_H_

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
// class Logger {
//  public:
//   enum class LogLevel { INFO, WARNING, ERROR, DEBUG };
//   LogLevel info = LogLevel::INFO, warning = LogLevel::WARNING,
//            error = LogLevel::ERROR, debug = LogLevel::DEBUG;

//   Logger() {}
// };

/**
 * Singleton class to provide simple logging functionality.
 */
class Logger {
 public:
  /**
   * This static method controls the access to the singleton.
   *
   * @return ref to the Logger singleton
   */
  static Logger &obj(const bool verbose = false, const bool quiet = false,
                     const bool noGestures = false,
                     const bool noUpdates = false) {
    static Logger singleton;

    if (singleton.uninitialized) {
      singleton.Init(verbose, quiet, noGestures, noUpdates);
    }

    return singleton;
  }

  /**
   * @return true if the logger should be called for gesture msgs. Necessary
   * because the logging funcs don't know what kind of msg is being passed.
   */
  bool gestures() { return logGestures; }

  /**
   * @return true if the logger should be called for gesture msgs. Necessary
   * because the logging funcs don't know what kind of msg is being passed.
   */
  bool gestureUpdates() { return logGestureUpdates; }

  // Should not be cloneable.
  Logger(Logger const &) = delete;

  // Should not be assignable.
  void operator=(Logger const &) = delete;

 private:
  // These indicate if the various logging levels should be enabled.
  bool logInfo, logWarning, logError, logDebug;

  // If true then gesture msgs should be logged.
  bool logGestures;

  // If true then gesture update % msgs should be logged.
  bool logGestureUpdates;

  /*
   * if true then the logging levels & options will be set on first call to
   * Logger::Obj()
   */
  bool uninitialized;

  Logger();

  void Init(const bool verbose = false, const bool quiet = false,
            const bool noGestures = false, const bool noUpdates = false);
};

#endif  // UTILS_LOGGER_H_

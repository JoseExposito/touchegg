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

enum class LogLevel { INFO, WARNING, ERROR, DEBUG, GESTURE_INFO, UPDATE_INFO };

namespace tlg {
extern LogLevel error;
extern LogLevel warning;
extern LogLevel info;
extern LogLevel debug;

extern LogLevel gesture;
extern LogLevel update;
}  // namespace tlg

/**
 * Singleton class to provide simple logging functionality.
 */
class Logger {
 public:
  /**
   * USAGE: LogLevel.LEVEL << "A very informative message!" << std::endl;
   *
   * LEVEL: info | warning | error | debug | gesture | update
   */
  friend LogLevel operator<<(const LogLevel &lvl,
                             std::ostream &(*msg)(std::ostream &));
  template <typename T>
  friend LogLevel operator<<(const LogLevel &lvl, T const &msg);

  /**
   * This static method controls the access to the singleton.
   *
   * The following parameters are only applied on the first call when the
   * singleton is created.
   * @param verbose Show all log msgs.
   * @param quiet Suppress all msgs.
   * @param noGestures Suppress gesture msgs.
   * @param noUpdates Suppress gesture update msgs.
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

  /**
   * If true then the logging levels & options will be set on first call to
   * Logger::Obj()
   */
  bool uninitialized;

  Logger();

  /**
   * Sets the logging levels & options.
   */
  void Init(const bool verbose, const bool quiet, const bool noGestures,
            const bool noUpdates);

  bool Enabled(const LogLevel &lvl);
  std::ostream &GetStream(const LogLevel &lvl);
};

/**
 * USAGE: LogLevel.LEVEL << "A very informative message!" << std::endl;
 *
 * LEVEL: info | warning | error | debug | gesture | update
 */
LogLevel operator<<(const LogLevel &lvl, std::ostream &(*msg)(std::ostream &));
template <typename T>
LogLevel operator<<(const LogLevel &lvl, T const &msg) {
  if (Logger::obj().Enabled(lvl)) {
    Logger::obj().GetStream(lvl) << msg;
  }

  return lvl;
}

#endif  // UTILS_LOGGER_H_

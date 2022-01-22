/**
 * Copyright 2021 John Mifsud <imabuddha@gmail.com>
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
#ifndef UTILS_ARGS_PARSER_H_
#define UTILS_ARGS_PARSER_H_

#include <string>
#include <vector>

class ArgsParser {
 public:
  /**
   * When constructed the obj parses the given args and sets the option flags
   *
   * @param argc The standard arg count passed to main()
   * @param argv The standard arg array passed to main()
   */
  ArgsParser(int argc, char **argv);

  /**
   * Print version number.
   */
  static void printVersion();

  /**
   * If should run in daemon mode.
   */
  bool daemonMode = false;

  /**
   * If should run in client mode.
   */
  bool clientMode = false;

  /**
   * If should show every log message.
   */
  bool debug = false;

  /**
   * If should not show any log message.
   */
  bool quiet = false;

  /**
   * Amount of motion to be made on the touchpad before a gesture is started.
   */
  double startThreshold = -1;

  /**
   * Amount of motion to be made on the touchpad to reach the end of the
   * gesture.
   */
  double finishThreshold = -1;

  /**
   * Flag indicating if the process should exit (--help, --version, etc).
   */
  bool exit = false;

 private:
  std::vector<std::string> tokens;

  bool cmdOptionExists(const std::string &option);

  /**
   * When 2 number are set after --daemon, use them as start and finish
   * thresholds.
   */
  void getDaemonThresholds();

  /**
   * Print help.
   */
  static void printHelp();
};

#endif  // UTILS_ARGS_PARSER_H_

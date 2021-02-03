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
#ifndef UTILS_ARGS_PARSER_H_
#define UTILS_ARGS_PARSER_H_

#include <string>
#include <vector>

#include "utils/logger.h"

class ArgsParser {
 public:
  /**
   * the option flags
   */
  bool daemonMode, clientMode;
  bool debug, quiet;
  double startThreshold = -1;
  double finishThreshold = -1;

  /**
   * When constructed the obj parses the given args and sets the option flags
   *
   * @param argc The standard arg count passed to main()
   * @param argv The standard arg array passed to main()
   */
  ArgsParser(int argc, char** argv);

 private:
  std::vector<std::string> tokens;

  const std::string getCmdOption(const std::string& option);
  void getCmdOption2d(const std::string& option, double* pd1, double* pd2);
  bool cmdOptionExists(const std::string& option);
};

#endif  // UTILS_ARGS_PARSER_H_

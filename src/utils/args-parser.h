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

#include "logger.h"

class ArgsParser {
 public:
  ArgsParser(int& argc, char** argv);

  const std::string getCmdOption(const std::string& option);

  // special case used for daemon thresholds
  void getCmdOption2d(const std::string& option, double& d1, double& d2);

  bool cmdOptionExists(const std::string& option);

 private:
  std::vector<std::string> tokens;
};

void parseArgs(int argc, char** argv, bool& daemonMode, bool& clientMode,
               double& startThreshold, double& finishThreshold);

#endif  // UTILS_ARGS_PARSER_H_

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
#include "args-parser.h"

#include <algorithm>

ArgsParser::ArgsParser(int& argc, char** argv) {
  // set defaults
  daemonMode = clientMode = false;
  startThreshold = finishThreshold = -1;

  // Parse the command line arguments
  for (int i = 1; i < argc; ++i) this->tokens.push_back(std::string(argv[i]));

  // daemon takes precedence over client
  if (cmdOptionExists("--daemon")) {
    daemonMode = true;
    getCmdOption2d("--daemon", startThreshold, finishThreshold);
  } else if (cmdOptionExists("--client") || (tokens.size() == 0)) {
    clientMode = true;
  }

  verbose = cmdOptionExists("--verbose") || cmdOptionExists("-v");
  quiet = cmdOptionExists("--quiet") || cmdOptionExists("-q");
  noGestures = cmdOptionExists("--no-gesture-messages");
  noUpdates = cmdOptionExists("--no-update-messages");
}

const std::string ArgsParser::getCmdOption(const std::string& option) {
  std::vector<std::string>::const_iterator itr;
  itr = std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
    return *itr;
  }
  static const std::string empty_string("");
  return empty_string;
}

// special case used for daemon thresholds
void ArgsParser::getCmdOption2d(const std::string& option, double& d1,
                                double& d2) {
  std::vector<std::string>::const_iterator itr;
  itr = std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr != this->tokens.end()) {
    if (++itr != this->tokens.end()) {
      d1 = std::stod(*itr);
      if (++itr != this->tokens.end()) {
        d2 = std::stod(*itr);
      }
    }
  }
}

bool ArgsParser::cmdOptionExists(const std::string& option) {
  return std::find(this->tokens.begin(), this->tokens.end(), option) !=
         this->tokens.end();
}

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
#include "utils/args-parser.h"

#include <algorithm>
#include <iostream>

#ifdef _VERSION
constexpr auto VERSION = _VERSION;
#else
constexpr auto VERSION = "[Unkown version]";
#endif

void printWelcomeMessage() {
  std::cout << "Touchégg " << VERSION << "." << std::endl;
  std::cout << "Usage: touchegg [--help] [--debug | -d] [--quiet | -q] "
               "[--daemon [start_threshold finish_threshold]] "
               "[--client]"
            << std::endl
            << std::endl;

  std::cout << "Multi-touch gesture recognizer." << std::endl;
  std::cout << "Touchégg is an app that runs in the background and transforms "
               "the gestures you make on your touchpad into visible actions in "
               "your desktop."
            << std::endl;
  std::cout << "For more information please visit:" << std::endl;
  std::cout << "https://github.com/JoseExposito/touchegg" << std::endl
            << std::endl;

  std::cout << "Option\t\tMeaning" << std::endl;
  std::cout << " --daemon\tRun Touchégg in daemon mode. This mode starts a "
               "service that gathers gestures but executes no actions"
            << std::endl;
  std::cout << " --client\tConnect to an existing Touchégg daemon and "
               "execute actions in your desktop"
            << std::endl;
  std::cout << "Without arguments Touchégg starts in client mode" << std::endl
            << std::endl;
}

ArgsParser::ArgsParser(int argc, char** argv) {
  // set defaults
  daemonMode = clientMode = false;
  startThreshold = finishThreshold = -1;

  // Parse the command line arguments
  for (int i = 1; i < argc; ++i) this->tokens.push_back(std::string(argv[i]));

  if (cmdOptionExists("--daemon")) {
    daemonMode = true;
    getCmdOption2d("--daemon", &startThreshold, &finishThreshold);
  }

  if (cmdOptionExists("--client") || (tokens.size() == 0)) {
    clientMode = true;
  }

  debug = cmdOptionExists("--debug") || cmdOptionExists("-d");
  quiet = cmdOptionExists("--quiet") || cmdOptionExists("-q");

  if (cmdOptionExists("--help")) {
    printWelcomeMessage();
  }
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
void ArgsParser::getCmdOption2d(const std::string& option, double* pd1,
                                double* pd2) {
  std::vector<std::string>::const_iterator itr;
  itr = std::find(this->tokens.begin(), this->tokens.end(), option);
  if (itr != this->tokens.end()) {
    if (++itr != this->tokens.end()) {
      *pd1 = std::stod(*itr);
      if (++itr != this->tokens.end()) {
        *pd2 = std::stod(*itr);
      }
    }
  }
}

bool ArgsParser::cmdOptionExists(const std::string& option) {
  return std::find(this->tokens.begin(), this->tokens.end(), option) !=
         this->tokens.end();
}

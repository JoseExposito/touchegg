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
#include "utils/args-parser.h"

#include <algorithm>
#include <iostream>

#ifdef _VERSION
constexpr auto VERSION = _VERSION;
#else
constexpr auto VERSION = "[Unkown version]";
#endif

ArgsParser::ArgsParser(int argc, char **argv)
    : tokens(argv + 1, argv + argc) {  // NOLINT
  this->daemonMode = cmdOptionExists("--daemon");
  this->clientMode = cmdOptionExists("--client") || !this->daemonMode;
  this->debug = cmdOptionExists("--debug") || cmdOptionExists("-d");
  this->quiet = cmdOptionExists("--quiet") || cmdOptionExists("-q");

  if (this->daemonMode) {
    this->getDaemonThresholds();
  }

  if (cmdOptionExists("--version") || cmdOptionExists("-v")) {
    ArgsParser::printVersion();
    this->exit = true;
  }

  if (cmdOptionExists("--help") || cmdOptionExists("-h")) {
    ArgsParser::printHelp();
    this->exit = true;
  }
}

bool ArgsParser::cmdOptionExists(const std::string &option) {
  return std::find(this->tokens.begin(), this->tokens.end(), option) !=
         this->tokens.end();
}

void ArgsParser::getDaemonThresholds() {
  try {
    auto itr = std::find(this->tokens.begin(), this->tokens.end(), "--daemon");
    if (itr != this->tokens.end()) {
      if (++itr != this->tokens.end()) {
        this->startThreshold = std::stod(*itr);
        if (++itr != this->tokens.end()) {
          this->finishThreshold = std::stod(*itr);
        } else {
          this->startThreshold = -1;
          this->finishThreshold = -1;
        }
      }
    }
  } catch (std::exception &e) {
    this->startThreshold = -1;
    this->finishThreshold = -1;
  }
}

void ArgsParser::printVersion() {
  std::cout << "Touchégg " << VERSION << "." << std::endl;
}

void ArgsParser::printHelp() {
  ArgsParser::printVersion();
  std::cout << "Usage: touchegg [--help | -h] [--version | -v] [--debug | -d] "
               "[--quiet | -q] [--daemon [start_threshold finish_threshold]] "
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
  std::cout << " --quiet\tDo not print to the log" << std::endl;
  std::cout << " --debug\tPrint every message to the log" << std::endl;
  std::cout << " --version\tPrint the version number and exit" << std::endl;
  std::cout << " --help \tPrint this message and exit" << std::endl;

  std::cout << "Without arguments Touchégg starts in client mode" << std::endl;
}

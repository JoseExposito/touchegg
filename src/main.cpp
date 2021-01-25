/**
 * Copyright 2011 - 2021 José Expósito <jose.exposito89@gmail.com>
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
#include <algorithm>
#include <iostream>
#include <string>

#include "config/config.h"
#include "config/xml-config-loader.h"
#include "daemon/daemon-client.h"
#include "daemon/daemon-server.h"
#include "gesture-controller/gesture-controller.h"
#include "gesture-gatherer/libinput-gesture-gatherer.h"
#include "utils/client-lock.h"
#include "utils/logger.h"
#include "window-system/window-system.h"
#include "window-system/x11.h"

#ifdef _VERSION
constexpr auto VERSION = _VERSION;
#else
constexpr auto VERSION = "[Unkown version]";
#endif
class InputParser {
 public:
  InputParser(int& argc, char** argv) {
    for (int i = 1; i < argc; ++i) this->tokens.push_back(std::string(argv[i]));
  }

  const std::string getCmdOption(const std::string& option) const {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
      return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
  }

  // special case used for daemon thresholds
  void getCmdOption2d(const std::string& option, double& d1, double& d2) const {
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

  bool cmdOptionExists(const std::string& option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) !=
           this->tokens.end();
  }

 private:
  std::vector<std::string> tokens;
};

// Parse the command line arguments
void parseArgs(int argc, char** argv, bool& daemonMode, bool& clientMode,
               double& startThreshold, double& finishThreshold) {
  bool verbose, quiet, noGestures, noUpdates;

  InputParser input(argc, argv);

  // daemon takes precedence over client
  if (input.cmdOptionExists("--daemon")) {
    daemonMode = true;
    input.getCmdOption2d("--daemon", startThreshold, finishThreshold);
  } else if (input.cmdOptionExists("--client") || (argc == 1)) {
    clientMode = true;
  }

  verbose = input.cmdOptionExists("--verbose") || input.cmdOptionExists("-v");
  quiet = input.cmdOptionExists("--quiet") || input.cmdOptionExists("-q");
  noGestures = input.cmdOptionExists("--no-gesture-messages");
  noUpdates = input.cmdOptionExists("--no-update-messages");

  // init Logger options
  Logger::obj(verbose, quiet, noGestures, noUpdates);
}

void printWelcomeMessage() {
  Logger& log = Logger::obj();
  log.info << "Touchégg " << VERSION << "." << std::endl;
  log.info << "Usage: touchegg [--verbose | -v] [--quiet | -q] "
              "[--no-gesture-messages] [--no-update-messages] "
              "[--daemon [start_threshold finish_threshold]] "
              "[--client]"
           << std::endl
           << std::endl;

  log.info << "Multi-touch gesture recognizer." << std::endl;
  log.info << "Touchégg is an app that runs in the background and transforms "
              "the gestures you make on your touchpad into visible actions in "
              "your desktop."
           << std::endl;
  log.info << "For more information please visit:" << std::endl;
  log.info << "https://github.com/JoseExposito/touchegg" << std::endl
           << std::endl;

  log.info << "Option\t\tMeaning" << std::endl;
  log.info << " --daemon\tRun Touchégg in daemon mode. This mode starts a "
              "service that gathers gestures but executes no actions"
           << std::endl;
  log.info << " --client\tConnect to an existing Touchégg daemon and "
              "execute actions in your desktop"
           << std::endl;
  log.info << "Without arguments Touchégg starts in client mode" << std::endl
           << std::endl;
}

int main(int argc, char** argv) {
  bool daemonMode = false;
  bool clientMode = false;
  double startThreshold = -1;
  double finishThreshold = -1;

  parseArgs(argc, argv, daemonMode, clientMode, startThreshold,
            finishThreshold);

  /**
   * if this convenience var is used in main() it MUST be declared after
   * parseArgs() so that Logger options are set properly!
   */
  Logger& log = Logger::obj();
  // // test log options
  // log.info << "A very informative message." << std::endl;
  // log.warning << "Warning!" << std::endl;
  // log.error << "ERROR!!!" << std::endl;
  // log.debug << "DBG: 0xdeadbeef" << std::endl;
  // log.gesture << "Nice gesture" << std::endl;
  // log.update << "G-Update" << std::endl;
  // log.info std::endl << std::endl << std::endl;

  printWelcomeMessage();

  if (!daemonMode && !clientMode) {
    log.error << "Invalid command line arguments" << std::endl;
    return -1;
  }

  log.info << "Starting Touchégg in "
           << (daemonMode ? std::string{"daemon mode"}
                          : std::string{"client mode"})
           << std::endl;

  // Execute the daemon/client bits
  if (daemonMode) {
    // Start the daemon server
    DaemonServer daemonServer{};
    daemonServer.run();

    // Use libinput as gesture gatherer
    log.info << "A list of detected compatible devices will be displayed below:"
             << std::endl;

    LibinputGestureGatherer gestureGatherer(&daemonServer, startThreshold,
                                            finishThreshold);
    gestureGatherer.run();
  }

  if (clientMode) {
    // Avoid running multiple client instances in parallel
    ClientLock lock;

    // Load the configuration using the XML loader
    log.info << "Parsing you configuration file..." << std::endl;
    Config config;
    XmlConfigLoader loader(&config);
    loader.load();
    log.info << "Configuration parsed successfully" << std::endl;

    // Use X11 as window system
    X11 windowSystem;

    // Initialize the gesture controller
    GestureController gestureController(config, windowSystem);

    // Connect to the daemon
    DaemonClient daemonClient{&gestureController};
    daemonClient.run();
  }
}

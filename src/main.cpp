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
#include <iostream>
#include <string>

#include "config/config.h"
#include "config/xml-config-loader.h"
#include "daemon/daemon-client.h"
#include "daemon/daemon-server.h"
#include "gesture-controller/gesture-controller.h"
#include "gesture-gatherer/libinput-gesture-gatherer.h"
#include "utils/args-parser.h"
#include "utils/client-lock.h"
#include "utils/logger.h"
#include "window-system/window-system.h"
#include "window-system/x11.h"

#ifdef _VERSION
constexpr auto VERSION = _VERSION;
#else
constexpr auto VERSION = "[Unkown version]";
#endif

void printWelcomeMessage() {
  tlg::info << "Touchégg " << VERSION << "." << std::endl;
  tlg::info << "Usage: touchegg [--debug | -d] [--quiet | -q] "
               "[--daemon [start_threshold finish_threshold]] "
               "[--client]"
            << std::endl
            << std::endl;

  tlg::info << "Multi-touch gesture recognizer." << std::endl;
  tlg::info << "Touchégg is an app that runs in the background and transforms "
               "the gestures you make on your touchpad into visible actions in "
               "your desktop."
            << std::endl;
  tlg::info << "For more information please visit:" << std::endl;
  tlg::info << "https://github.com/JoseExposito/touchegg" << std::endl
            << std::endl;

  tlg::info << "Option\t\tMeaning" << std::endl;
  tlg::info << " --daemon\tRun Touchégg in daemon mode. This mode starts a "
               "service that gathers gestures but executes no actions"
            << std::endl;
  tlg::info << " --client\tConnect to an existing Touchégg daemon and "
               "execute actions in your desktop"
            << std::endl;
  tlg::info << "Without arguments Touchégg starts in client mode" << std::endl
            << std::endl;
}

int main(int argc, char** argv) {
  ArgsParser args(argc, argv);

  // init Logger options
  Logger::obj(args.debug, args.quiet);

  // test log options
  tlg::error << "ERROR!!!" << std::endl;
  tlg::warning << "Warning!" << std::endl;
  tlg::info << "A very informative message." << std::endl;
  tlg::debug << "DBG: 0xdeadbeef" << std::endl;
  tlg::error << std::endl << std::endl;

  printWelcomeMessage();

  if (args.daemonMode == args.clientMode) {
    tlg::error << "Invalid command line arguments" << std::endl;
    return -1;
  }

  std::time_t t = std::time(NULL);
  char mbstr[100];
  std::strftime(mbstr, sizeof(mbstr) - 1, "[%F-%T%z] ", std::localtime(&t));
  tlg::info << mbstr << "Starting Touchégg in "
            << (args.daemonMode ? std::string{"daemon mode"}
                                : std::string{"client mode"})
            << std::endl;

  // Execute the daemon/client bits
  if (args.daemonMode) {
    // Start the daemon server
    DaemonServer daemonServer{};
    daemonServer.run();

    // Use libinput as gesture gatherer
    tlg::info
        << "A list of detected compatible devices will be displayed below:"
        << std::endl;

    LibinputGestureGatherer gestureGatherer(&daemonServer, args.startThreshold,
                                            args.finishThreshold);
    gestureGatherer.run();
  } else {  // clientMode
    // Avoid running multiple client instances in parallel
    ClientLock lock;

    // Load the configuration using the XML loader
    tlg::info << "Parsing your configuration file..." << std::endl;
    Config config;
    XmlConfigLoader loader(&config);
    loader.load();
    tlg::info << "Configuration parsed successfully" << std::endl;

    // Use X11 as window system
    X11 windowSystem;

    // Initialize the gesture controller
    GestureController gestureController(config, windowSystem);

    // Connect to the daemon
    DaemonClient daemonClient{&gestureController};
    daemonClient.run();
  }
}

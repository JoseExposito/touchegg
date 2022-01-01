/**
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

int main(int argc, char** argv) {
  // Parse the command line arguments
  ArgsParser args(argc, argv);
  if (args.exit) {
    return 0;
  }
  ArgsParser::printVersion();

  // Configure the logger
  tlg::configure(args.debug, args.quiet);

  if (args.daemonMode == args.clientMode) {
    tlg::error << "Invalid command line arguments" << std::endl;
    return -1;
  }

  tlg::info << "Starting Touchégg in "
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
    // Use X11 as window system
    X11 windowSystem;

    // Avoid running multiple client instances in parallel
    ClientLock lock(windowSystem.getConnectionName());

    // Load the configuration using the XML loader
    tlg::info << "Parsing your configuration file..." << std::endl;
    Config config;
    XmlConfigLoader loader(&config);
    loader.load();
    tlg::info << "Configuration parsed successfully" << std::endl;

    // Initialize the gesture controller
    GestureController gestureController(config, windowSystem);

    // Connect to the daemon
    DaemonClient daemonClient{&gestureController};
    daemonClient.run();
  }
}

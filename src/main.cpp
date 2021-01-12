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
#include "utils/client-lock.h"
#include "window-system/window-system.h"
#include "window-system/x11.h"

#ifdef _VERSION
constexpr auto VERSION = _VERSION;
#else
constexpr auto VERSION = "[Unkown version]";
#endif

void printWelcomeMessage() {
  std::cout << "Touchégg " << VERSION << "." << std::endl;
  std::cout << "Usage: touchegg [--daemon [start_threshold finish_threshold]] "
               "[--client]"
            << std::endl
            << std::endl;

  std::cout << "Multi-touch gesture recognizer." << std::endl;
  std::cout << "Touchégg is an app that runs in the background and transform "
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

int main(int argc, char **argv) {
  printWelcomeMessage();

  // Parse the command line arguments
  bool daemonMode = false;
  bool clientMode = (argc == 1);
  double startThreshold = -1;
  double finishThreshold = -1;

  if (argc > 1) {
    std::string param{argv[1]};  // NOLINT
    daemonMode = (param == "--daemon");
    clientMode = (param == "--client");

    if (daemonMode && argc == 4) {
      startThreshold = std::stod(argv[2]);   // NOLINT
      finishThreshold = std::stod(argv[3]);  // NOLINT
    }
  }

  if (!daemonMode && !clientMode) {
    std::cout << "Invalid command line arguments" << std::endl;
    return -1;
  }

  std::cout << "Starting Touchégg in "
            << (daemonMode ? std::string{"daemon mode"}
                           : std::string{"client mode"})
            << std::endl;

  // Execute the daemon/client bits
  if (daemonMode) {
    // Start the daemon server
    DaemonServer daemonServer{};
    daemonServer.run();

    // Use libinput as gesture gatherer
    std::cout
        << "A list of detected compatible devices will be displayed below:"
        << std::endl;

    LibinputGestureGatherer gestureGatherer(&daemonServer, startThreshold,
                                            finishThreshold);
    gestureGatherer.run();
  }

  if (clientMode) {
    // Avoid running multiple client instances in parallel
    ClientLock lock;

    // Load the configuration using the XML loader
    std::cout << "Parsing you configuration file..." << std::endl;
    Config config;
    XmlConfigLoader loader(&config);
    loader.load();
    std::cout << "Configuration parsed successfully" << std::endl;

    // Use X11 as window system
    X11 windowSystem;

    // Initialize the gesture controller
    GestureController gestureController(config, windowSystem);

    // Connect to the daemon
    DaemonClient daemonClient{&gestureController};
    daemonClient.run();
  }
}

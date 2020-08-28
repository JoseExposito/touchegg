/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
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

#include "config/config.h"
#include "config/xml-config-loader.h"
#include "gesture-controller/gesture-controller.h"
#include "gesture-gatherer/libinput-gesture-gatherer.h"
#include "window-system/window-system.h"
#include "window-system/x11.h"

int main(/* int, char ** */) {
  std::cout << "Starting Touchégg..." << std::endl;

  // Load the configuration using the XML loader
  Config config;
  XmlConfigLoader loader(&config);
  loader.load();

  // Use X11 as window system
  X11 windowSystem;

  // Initialize the gesture controller
  GestureController gestureController(config, windowSystem);

  // Use libinput as gesture gatherer
  LibinputGestureGatherer gestureGatherer(config, &gestureController);
  gestureGatherer.run();
}

/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
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
#ifndef DAEMON_DAEMON_CLIENT_H_
#define DAEMON_DAEMON_CLIENT_H_

#include <memory>

#include "daemon/gesture-event.h"
#include "gesture-controller/gesture-controller-delegate.h"
#include "gesture/gesture.h"
#include "window-system/window-system.h"

/**
 * Class to connect to the daemon server and send the gestures received from the
 * server to the GestureControllerDelegate.
 */
class DaemonClient {
 public:
  explicit DaemonClient(GestureControllerDelegate *gestureController)
      : gestureController(gestureController) {}

  void run();

 private:
  GestureControllerDelegate *gestureController;

  void sendToGestureController(const struct GestureEvent &event);

  std::unique_ptr<Gesture> makeGestureFromEvent(
      const struct GestureEvent &event) const;
};

#endif  // DAEMON_DAEMON_CLIENT_H_

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
#ifndef DAEMON_DAEMON_SERVER_H_
#define DAEMON_DAEMON_SERVER_H_

#include <memory>
#include <vector>

#include "daemon/gesture-event.h"
#include "gesture-controller/gesture-controller-delegate.h"

/**
 * Access to libinput is limited to users in the "input" group or, in the case
 * of Wayland, to the compositor. However, adding your user to the "input" group
 * is insecure because then any process you execute will have full access, for
 * example, to your keyboard input.
 *
 * To avoid this security issue, Touchégg can be executed as a daemon by systemd
 * so only the daemon have access to libinput.
 * The daemon uses this class to start a Unix domain socket server and expose
 * only the minimum required libinput information.
 */
class DaemonServer : public GestureControllerDelegate {
 public:
  void run();

  void onGestureBegin(std::unique_ptr<Gesture> gesture) override;
  void onGestureUpdate(std::unique_ptr<Gesture> gesture) override;
  void onGestureEnd(std::unique_ptr<Gesture> gesture) override;

 private:
  int socket;
  std::vector<int> clients;

  void send(GestureEventType eventType, std::unique_ptr<Gesture> gesture);
};

#endif  // DAEMON_DAEMON_SERVER_H_

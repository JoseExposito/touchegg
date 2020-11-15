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
#include "daemon/daemon-client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <chrono>  // NOLINT
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>  // NOLINT
#include <utility>
#include <vector>

void DaemonClient::run() {
  std::cout << "Connecting to Touchégg daemon..." << std::endl;

  int socket = -1;
  bool connected = false;

  // Stuct to store the received event. It is usefull to keep it to be able to
  // finish ongoing actions in case of disconnection
  GestureEvent event{};

  while (true) {
    if (!connected) {
      socket = ::socket(AF_UNIX, SOCK_STREAM, 0);
      if (socket == -1) {
        throw std::runtime_error{
            "Error connecting to Touchégg daemon: Can not create socket"};
      }

      struct sockaddr_un addr = {};
      addr.sun_family = AF_UNIX;
      std::memset(&addr.sun_path[0], 0, sizeof(addr.sun_path));
      SOCKET_NAME.copy(&addr.sun_path[0], SOCKET_NAME.size(), 0);

      auto socketAddr = reinterpret_cast<sockaddr *>(&addr);  // NOLINT
      if (connect(socket, socketAddr, sizeof(addr)) == -1) {
        connected = false;
      } else {
        std::cout << "Successfully connected to Touchégg daemon" << std::endl;
        connected = true;
      }
    }

    if (connected) {
      int total = read(socket, &event, sizeof(event));
      if (total <= 0) {
        connected = false;
      } else {
        this->sendToGestureController(event);
      }
    }

    if (!connected) {
      std::cout << "Connection with Touchégg daemon lost. "
                   "Reconnecting in 5 seconds..."
                << std::endl;

      if (event.eventType != GestureEventType::UNKNOWN &&
          event.eventType != GestureEventType::END) {
        event.eventType = GestureEventType::END;
        this->sendToGestureController(event);
      }

      close(socket);
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  }
}

void DaemonClient::sendToGestureController(const struct GestureEvent &event) {
  std::unique_ptr<Gesture> gesture = this->makeGestureFromEvent(event);
  switch (event.eventType) {
    case GestureEventType::BEGIN:
      this->gestureController->onGestureBegin(std::move(gesture));
      break;
    case GestureEventType::UPDATE:
      this->gestureController->onGestureUpdate(std::move(gesture));
      break;
    case GestureEventType::END:
      this->gestureController->onGestureEnd(std::move(gesture));
      break;
    default:
      break;
  }
}

std::unique_ptr<Gesture> DaemonClient::makeGestureFromEvent(
    const struct GestureEvent &event) const {
  return std::make_unique<Gesture>(
      event.type, event.direction, event.percentage, event.fingers,
      event.performedOnDeviceType, event.elapsedTime);
}

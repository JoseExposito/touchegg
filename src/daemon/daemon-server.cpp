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
#include "daemon/daemon-server.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>  // NOLINT
#include <utility>

void DaemonServer::run() {
  std::cout << "Starting daemon server..." << std::endl;

  this->socket = ::socket(AF_UNIX, SOCK_STREAM, 0);
  if (this->socket == -1) {
    throw std::runtime_error{"Error starting server: Can not create socket"};
  }

  struct sockaddr_un addr = {};
  addr.sun_family = AF_UNIX;
  std::memset(&addr.sun_path[0], 0, sizeof(addr.sun_path));
  SOCKET_NAME.copy(&addr.sun_path[0], SOCKET_NAME.size(), 0);

  auto socketAddr = reinterpret_cast<sockaddr *>(&addr);  // NOLINT
  if (bind(this->socket, socketAddr, sizeof(addr)) == -1) {
    throw std::runtime_error{"Error starting server: Can not bind socket"};
  }

  if (::listen(this->socket, 10) == -1) {
    throw std::runtime_error{"Error starting server: Socket listen"};
  }

  std::cout << "Server started" << std::endl;

  std::thread connectThread{[this]() {
    while (true) {
      struct sockaddr_in clientAddr = {};
      socklen_t clientAddrLength = sizeof(clientAddr);
      auto socketAddrIn = reinterpret_cast<sockaddr *>(&clientAddr);  // NOLINT
      int client = accept(this->socket, socketAddrIn, &clientAddrLength);

      if (client != -1) {
        std::cout << "New client connected with ID: " << client << std::endl;
        this->clients.push_back(client);
      }
    }
  }};
  connectThread.detach();
}

void DaemonServer::onGestureBegin(std::unique_ptr<Gesture> gesture) {
  this->send(GestureEventType::BEGIN, std::move(gesture));
}

void DaemonServer::onGestureUpdate(std::unique_ptr<Gesture> gesture) {
  this->send(GestureEventType::UPDATE, std::move(gesture));
}

void DaemonServer::onGestureEnd(std::unique_ptr<Gesture> gesture) {
  this->send(GestureEventType::END, std::move(gesture));
}

void DaemonServer::send(GestureEventType eventType,
                        std::unique_ptr<Gesture> gesture) {
  // Copy every gesture field into the struct for serialization
  GestureEvent event{};
  event.eventSize = sizeof(GestureEvent);
  event.eventType = eventType;
  event.type = gesture->type();
  event.direction = gesture->direction();
  event.percentage = gesture->percentage();
  event.fingers = gesture->fingers();
  event.elapsedTime = gesture->elapsedTime();
  event.performedOnDeviceType = gesture->performedOnDeviceType();

  // Send the gesture event to every client
  std::vector<int> disconnectedClients{};

  for (auto client : this->clients) {
    int written = write(client, &event, event.eventSize);

    if (written < 0) {
      std::cout << "Error sending message to client with ID " << client
                << ". Client disconnected" << std::endl;
      disconnectedClients.push_back(client);
    }
  }

  // Disconnect dead clients
  for (auto client : disconnectedClients) {
    this->clients.erase(
        std::remove(this->clients.begin(), this->clients.end(), client),
        this->clients.end());
  }
}

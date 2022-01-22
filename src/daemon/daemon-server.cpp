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
#include "daemon/daemon-server.h"

#include <gio/gio.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>  // NOLINT
#include <utility>

#include "daemon/dbus.h"
#include "utils/logger.h"

void DaemonServer::run() {
  tlg::info << "Starting daemon server..." << std::endl;
  GError *error = nullptr;

  tlg::info << "Generating D-Bus introspection data" << std::endl;
  this->introspectionData =
      g_dbus_node_info_new_for_xml(DBUS_INTROSPECTION_XML, &error);

  if (introspectionData == nullptr) {
    std::string errorMessage{"Error generating D-Bus introspection data: "};
    errorMessage += error->message;
    throw std::runtime_error{errorMessage};
  }

  tlg::info << "Creating D-Bus server" << std::endl;
  gchar *guid = g_dbus_generate_guid();

  GDBusServer *server = g_dbus_server_new_sync(
      DBUS_ADDRESS, G_DBUS_SERVER_FLAGS_NONE, guid, nullptr, nullptr, &error);

  if (server == nullptr) {
    std::string errorMessage{"Error creating D-Bus server: "};
    errorMessage += error->message;
    throw std::runtime_error{errorMessage};
  }

  g_dbus_server_start(server);
  g_free(guid);

  tlg::info << "Server started at address "
            << g_dbus_server_get_client_address(server) << std::endl;

  g_signal_connect(
      server, "new-connection",
      reinterpret_cast<GCallback>(DaemonServer::onNewConnection),  // NOLINT
      this);

  std::thread connectThread{[this]() {
    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
    g_main_loop_run(loop);
  }};
  connectThread.detach();
}

gboolean DaemonServer::onNewConnection(GDBusServer * /*server*/,
                                       GDBusConnection *connection,
                                       DaemonServer *self) {
  Logger &log = Logger::obj();
  tlg::info << "New client connection request" << std::endl;

  GDBusInterfaceVTable interfaceVTable{nullptr, nullptr, nullptr};
  int id = g_dbus_connection_register_object(
      connection, DBUS_OBJECT_PATH,
      self->introspectionData->interfaces[0],  // NOLINT
      &interfaceVTable, nullptr, nullptr, nullptr);

  if (id == 0) {
    tlg::error << "Error connecting client" << std::endl;
    return FALSE;
  }

  tlg::info << "New client connected" << std::endl;
  g_object_ref(connection);
  self->connections.push_back(connection);
  return TRUE;
}

void DaemonServer::onGestureBegin(std::unique_ptr<Gesture> gesture) {
  this->send(DBUS_ON_GESTURE_BEGIN, std::move(gesture));
}

void DaemonServer::onGestureUpdate(std::unique_ptr<Gesture> gesture) {
  this->send(DBUS_ON_GESTURE_UPDATE, std::move(gesture));
}

void DaemonServer::onGestureEnd(std::unique_ptr<Gesture> gesture) {
  this->send(DBUS_ON_GESTURE_END, std::move(gesture));
}

void DaemonServer::send(const std::string &signalName,
                        std::unique_ptr<Gesture> gesture) {
  std::vector<GDBusConnection *> closedConnections{};

  // Copy every gesture field into the signal parameters for serialization
  GVariant *signalParams =
      g_variant_new("(uudiut)",                              // NOLINT
                    static_cast<int>(gesture->type()),       // u
                    static_cast<int>(gesture->direction()),  // u
                    gesture->percentage(),                   // d
                    gesture->fingers(),                      // i
                    static_cast<int>(gesture->performedOnDeviceType()),  // u
                    gesture->elapsedTime());                             // t
  g_variant_ref_sink(signalParams);

  // Send the message to every client
  for (auto *connection : this->connections) {
    if (g_dbus_connection_is_closed(connection) == TRUE) {
      closedConnections.push_back(connection);
    } else {
      GError *error = nullptr;
      gboolean sent = g_dbus_connection_emit_signal(
          connection, nullptr, DBUS_OBJECT_PATH, DBUS_INTERFACE_NAME,
          signalName.c_str(), signalParams, &error);
      if (sent == FALSE) {
        tlg::error << "Error sending message: " << error->message << std::endl;
        closedConnections.push_back(connection);
      }
    }
  }

  g_variant_unref(signalParams);

  // Remove dead clients
  for (auto *connection : closedConnections) {
    tlg::info << "Client disconnected" << std::endl;
    this->connections.erase(std::remove(this->connections.begin(),
                                        this->connections.end(), connection),
                            this->connections.end());
    g_dbus_connection_close_sync(connection, nullptr, nullptr);
    g_object_unref(connection);
  }
}

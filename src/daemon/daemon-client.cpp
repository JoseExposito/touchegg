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
#include "daemon/daemon-client.h"

#include <gio/gio.h>

#include <chrono>  // NOLINT
#include <iostream>
#include <memory>
#include <string>
#include <thread>  // NOLINT
#include <utility>
#include <vector>

#include "daemon/dbus.h"
#include "utils/logger.h"

void DaemonClient::run() {
  this->connect();
  GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
  g_main_loop_run(loop);
}

void DaemonClient::connect() {
  tlg::info << "Connecting to Touchégg daemon..." << std::endl;

  bool connected = false;

  while (!connected) {
    GError *error = nullptr;
    GDBusConnection *connection = g_dbus_connection_new_for_address_sync(
        DBUS_ADDRESS, G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT, nullptr,
        nullptr, &error);

    connected = (connection != nullptr);

    if (!connected) {
      tlg::error << "Error connecting to Touchégg daemon: " << error->message
                 << std::endl;
      tlg::error << "Reconnecting in 5 seconds..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(5));
    } else {
      tlg::info << "Connection with Touchégg established" << std::endl;
      g_dbus_connection_signal_subscribe(
          connection, nullptr, DBUS_INTERFACE_NAME, nullptr, DBUS_OBJECT_PATH,
          nullptr, G_DBUS_SIGNAL_FLAGS_NONE, DaemonClient::onNewMessage, this,
          nullptr);

      g_signal_connect(
          connection, "closed",
          reinterpret_cast<GCallback>(DaemonClient::onDisconnected),  // NOLINT
          this);
    }
  }
}

void DaemonClient::onNewMessage(GDBusConnection * /*connection*/,
                                const gchar * /*senderName*/,
                                const gchar * /*objectPath*/,
                                const gchar * /*interfaceName*/,
                                const gchar *signalName, GVariant *parameters,
                                gpointer thisPointer) {
  auto *self = reinterpret_cast<DaemonClient *>(thisPointer);  // NOLINT

  if (self->lastSignalParams != nullptr) {
    g_variant_unref(self->lastSignalParams);
  }

  g_variant_ref(parameters);
  self->lastSignalName = signalName;
  self->lastSignalParams = parameters;

  self->sendToGestureController(signalName, parameters);
}

void DaemonClient::onDisconnected(GDBusConnection * /*connection*/,
                                  gboolean /*remotePeerVanished*/,
                                  GError *error, DaemonClient *self) {
  tlg::error << "Connection with Touchégg daemon lost "
             << (error == nullptr ? "" : error->message) << std::endl;

  if (self->lastSignalName == DBUS_ON_GESTURE_BEGIN ||
      self->lastSignalName == DBUS_ON_GESTURE_UPDATE) {
    std::unique_ptr<Gesture> gesture =
        DaemonClient::makeGestureFromSignalParams(self->lastSignalParams);
    self->gestureController->onGestureEnd(std::move(gesture));
  }

  self->connect();
}

void DaemonClient::sendToGestureController(const std::string &signalName,
                                           GVariant *signalParameters) {
  std::unique_ptr<Gesture> gesture =
      DaemonClient::makeGestureFromSignalParams(signalParameters);

  if (signalName == DBUS_ON_GESTURE_BEGIN) {
    this->gestureController->onGestureBegin(std::move(gesture));
  } else if (signalName == DBUS_ON_GESTURE_UPDATE) {
    this->gestureController->onGestureUpdate(std::move(gesture));
  } else if (signalName == DBUS_ON_GESTURE_END) {
    this->gestureController->onGestureEnd(std::move(gesture));
  }
}

std::unique_ptr<Gesture> DaemonClient::makeGestureFromSignalParams(
    GVariant *signalParameters) {
  GestureType type = GestureType::NOT_SUPPORTED;
  GestureDirection direction = GestureDirection::UNKNOWN;
  double percentage = -1;
  int fingers = -1;
  DeviceType deviceType = DeviceType::UNKNOWN;
  uint64_t elapsedTime = -1;

  g_variant_get(signalParameters,  // NOLINT
                "(uudiut)", &type, &direction, &percentage, &fingers,
                &deviceType, &elapsedTime);

  return std::make_unique<Gesture>(type, direction, percentage, fingers,
                                   deviceType, elapsedTime);
}

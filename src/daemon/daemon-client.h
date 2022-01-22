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
#ifndef DAEMON_DAEMON_CLIENT_H_
#define DAEMON_DAEMON_CLIENT_H_

#include <gio/gio.h>

#include <memory>
#include <string>

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

  /*
   * Store the last received signal and signal parameters so in case of
   * disconnection in the middle of a gesture we can finish it.
   */
  std::string lastSignalName = "";
  GVariant *lastSignalParams = nullptr;

  /**
   * Stablish a connection with the daemon server.
   */
  void connect();

  /**
   * Callback invoked when a new message is received.
   * @param connection The D-Bus connection.
   * @param senderName Unique bus name of the sender of the signal.
   * @param objectPath The object path that the signal was emitted on.
   * @param interfaceName The name of the interface.
   * @param signalName DBUS_ON_GESTURE_BEGIN, DBUS_ON_GESTURE_UPDATE or
   * DBUS_ON_GESTURE_END.
   * @param parameters Gesture params.
   * @param thisPointer this.
   */
  static void onNewMessage(GDBusConnection *connection, const gchar *senderName,
                           const gchar *objectPath, const gchar *interfaceName,
                           const gchar *signalName, GVariant *parameters,
                           gpointer thisPointer);

  /**
   * Callback invoked when the connection is closed.
   * @param connection The D-Bus connection.
   * @param remotePeerVanished TRUE if connection is closed because the remote
   * peer closed its end of the connection.
   * @param error Error reason or null.
   * @param self this.
   */
  static void onDisconnected(GDBusConnection *connection,
                             gboolean remotePeerVanished, GError *error,
                             DaemonClient *self);

  /**
   * Transform the signal into a gesture and send it to the controller.
   * @param signalName DBUS_ON_GESTURE_BEGIN, DBUS_ON_GESTURE_UPDATE or
   * DBUS_ON_GESTURE_END.
   * @param parameters Gesture params.
   */
  void sendToGestureController(const std::string &signalName,
                               GVariant *signalParameters);

  /**
   * Create a gesture from the received signal message.
   * @param signalParameters Received signal parameters.
   * @returns The gesture.
   */
  static std::unique_ptr<Gesture> makeGestureFromSignalParams(
      GVariant *signalParameters);
};

#endif  // DAEMON_DAEMON_CLIENT_H_

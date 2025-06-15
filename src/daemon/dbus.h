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
#ifndef DAEMON_DBUS_H_
#define DAEMON_DBUS_H_

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
constexpr auto DBUS_ADDRESS = "unix:path=/tmp/touchegg#0";
#else
constexpr auto DBUS_ADDRESS = "unix:abstract=touchegg";
#endif

// Singular is legacy
constexpr auto DBUS_OBJECT_PATH = "/io/github/joseexposito/Touchegg";
// New versions should be appended to the bottom of the list
constexpr const char* DBUS_OBJECT_PATHS[] = {
	"/io/github/joseexposito/Touchegg",	// 0 for legacy
	"/io/github/joseexposito/Touchegg1"
};

// Singular is legacy
constexpr auto DBUS_INTERFACE_NAME = "io.github.joseexposito.Touchegg";
// New versions should be appended to the bottom of the list
constexpr const char* DBUS_INTERFACE_NAMES[] = {
	"io.github.joseexposito.Touchegg",	// 0 for legacy
	"io.github.joseexposito.Touchegg1"
};

constexpr auto DBUS_ON_GESTURE_BEGIN = "OnGestureBegin";
constexpr auto DBUS_ON_GESTURE_UPDATE = "OnGestureUpdate";
constexpr auto DBUS_ON_GESTURE_END = "OnGestureEnd";

// Versions should be in order from oldest to newest
constexpr auto DBUS_INTROSPECTION_XML =
    "<node>"
    "  <interface name='io.github.joseexposito.Touchegg'>"
    "    <signal name='OnGestureBegin'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    "    </signal>"
    "    <signal name='OnGestureUpdate'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    "    </signal>"
    "    <signal name='OnGestureEnd'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    "    </signal>"
    "  </interface>"
    "  <interface name='io.github.joseexposito.Touchegg1'>"
    "    <signal name='OnGestureBegin'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='gesture_axis' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    "    </signal>"
    "    <signal name='OnGestureUpdate'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='gesture_axis' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    "    </signal>"
    "    <signal name='OnGestureEnd'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='gesture_axis' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    "    </signal>"
    "  </interface>"
    "</node>";

#endif  // DAEMON_DBUS_H_

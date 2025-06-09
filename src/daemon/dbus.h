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

constexpr auto DBUS_OBJECT_PATH = "/io/github/joseexposito/Touchegg";

constexpr auto DBUS_INTERFACE_NAME = "io.github.joseexposito.Touchegg";

constexpr auto DBUS_ON_GESTURE_BEGIN = "OnGestureBegin";
constexpr auto DBUS_ON_GESTURE_UPDATE = "OnGestureUpdate";
constexpr auto DBUS_ON_GESTURE_END = "OnGestureEnd";

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
    //"      <arg name='cursor_end_position' type='uu' />"
    //"      <arg name='cursor_end_position' type='x' />"
    "      <arg name='cursor_end_position' type='dd' />"
    //"      <arg name='maybe_cursor_end_position' type='m' />"
    //"      <arg name='cursor_end_position' type='(dd)' />"
    //"      <arg name='cursor_end_position' type='m@(dd)' />"
    //"      <arg name='cursor_end_position' type='m(dd)' />"
    //"      <arg name='cursor_end_position_x' type='d' />"
    //"      <arg name='cursor_end_position_y' type='d' />"
    "    </signal>"
    "    <signal name='OnGestureEnd'>"
    "      <arg name='gesture_type' type='u' />"
    "      <arg name='gesture_direction' type='u' />"
    "      <arg name='percentage' type='d' />"
    "      <arg name='fingers' type='i' />"
    "      <arg name='performed_on_device_type' type='u' />"
    "      <arg name='elapsed_time' type='t' />"
    //"      <arg name='cursor_end_position' type='uu' />"
    //"      <arg name='cursor_end_position' type='x' />"
    "      <arg name='cursor_end_position' type='dd' />"
    //"      <arg name='maybe_cursor_end_position' type='m' />"
    //"      <arg name='cursor_end_position' type='(dd)' />"
    //"      <arg name='cursor_end_position' type='m@(dd)' />"
    //"      <arg name='cursor_end_position' type='m(dd)' />"
    //"      <arg name='cursor_end_position_x' type='d' />"
    //"      <arg name='cursor_end_position_y' type='d' />"
    "    </signal>"
    "  </interface>"
    "</node>";

#endif  // DAEMON_DBUS_H_

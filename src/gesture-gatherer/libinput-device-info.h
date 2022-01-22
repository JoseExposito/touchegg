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
#ifndef GESTURE_GATHERER_LIBINPUT_DEVICE_INFO_H_
#define GESTURE_GATHERER_LIBINPUT_DEVICE_INFO_H_

/**
 * Data structure to save pre-calculated device information in the device user
 * data:
 * https://wayland.freedesktop.org/libinput/doc/latest/api/group__device.html#ga6243ad6005b2ce2a5ecfd1b04787fe93
 */
struct LibinputDeviceInfo {
  double startThreshold = 200;
  double finishThresholdHorizontal = 2500;
  double finishThresholdVertical = 2500;
};

#endif  // GESTURE_GATHERER_LIBINPUT_DEVICE_INFO_H_

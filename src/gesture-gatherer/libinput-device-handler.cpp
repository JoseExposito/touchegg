
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
#include "gesture-gatherer/libinput-device-handler.h"

#include <libinput.h>

#include <algorithm>
#include <iostream>

#include "gesture-gatherer/libinput-device-info.h"

void LininputDeviceHandler::handleDeviceAdded(
    struct libinput_event *event) const {
  struct libinput_device *device = libinput_event_get_device(event);
  if (libinput_device_has_capability(device, LIBINPUT_DEVICE_CAP_GESTURE) !=
      0) {
    std::cout << "Compatible device detected:" << std::endl;

    const char *name = libinput_device_get_name(device);
    std::cout << "\tName: " << name << std::endl;

    auto info = new LibinputDeviceInfo{};  // NOLINT

    double widthMm = 0;
    double heightMm = 0;
    if (libinput_device_get_size(device, &widthMm, &heightMm) == 0) {
      // From the official documentation:
      // https://wayland.freedesktop.org/libinput/doc/latest/normalization-of-relative-motion.html#motion-normalization
      //
      // libinput does partial normalization of relative input. For devices
      // with a resolution of 1000dpi and higher, motion events are
      // normalized to a default of 1000dpi before pointer acceleration is
      // applied.
      //
      // Touchpads may have a different resolution for the horizontal and
      // vertical axis. Interpreting coordinates from the touchpad without
      // taking resolution into account results in uneven motion.
      // libinput scales unaccelerated touchpad motion to the resolution of
      // the touchpad’s x axis, i.e. the unaccelerated value for the y axis
      // is: y = (x / resolution_x) * resolution_y.

      // Size is expressed in mm, but gesture deltaX/Y is normalized to
      // 1000dpi, thus, calculate how the maximum deltaX/Y and set:
      //  - threshold -> 2% of the maximum deltaX/Y
      //  - animation_finish_threshold -> 10% of the maximum deltaX/Y
      std::cout << "\tSize: " << widthMm << "mm x " << heightMm << "mm"
                << std::endl;

      std::cout << "\tCalculating threshold and animation_finish_threshold. "
                   "You can tune this values in your service file"
                << std::endl;

      double minSize = std::min(widthMm, heightMm);
      double inches = minSize / 25.4;  // 1 inch == 25.4 mm
      double dpi = (inches * 1000);
      info->threshold = ((2 * dpi) / 100);
      info->animationFinishThreshold = ((10 * dpi) / 100);
    } else {
      std::cout
          << "\tIt wasn't possible to get your device physical size, falling "
             "back to default threshold and animation_finish_threshold. You "
             "can tune this values in your service file"
          << std::endl;
    }

    // User preferences override the thresholds
    if (this->threshold != -1) {
      info->threshold = this->threshold;
    }

    if (this->animationFinishThreshold != -1) {
      info->animationFinishThreshold = this->animationFinishThreshold;
    }

    std::cout << "\tthreshold: " << info->threshold << std::endl;
    std::cout << "\tanimation_finish_threshold: "
              << info->animationFinishThreshold << std::endl;

    libinput_device_set_user_data(device, static_cast<void *>(info));

    libinput_event_destroy(event);
  }
}

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
#include "gesture-gatherer/libinput-device-handler.h"

#include <libinput.h>

#include <algorithm>
#include <iostream>

#include "gesture-gatherer/libinput-device-info.h"
#include "utils/logger.h"

void LininputDeviceHandler::handleDeviceAdded(
    struct libinput_event *event) const {
  struct libinput_device *device = libinput_event_get_device(event);

  bool hasGestureCap =
      libinput_device_has_capability(device, LIBINPUT_DEVICE_CAP_GESTURE) != 0;
  bool hasTouchCap =
      libinput_device_has_capability(device, LIBINPUT_DEVICE_CAP_TOUCH) != 0;

  if (hasGestureCap || hasTouchCap) {
    tlg::info << "Compatible device detected:" << std::endl;

    const char *name = libinput_device_get_name(device);
    tlg::info << "\tName: " << name << std::endl;

    auto info = new LibinputDeviceInfo{};  // NOLINT

    double widthMm = 0;
    double heightMm = 0;
    int getSizeStatus = libinput_device_get_size(device, &widthMm, &heightMm);

    // Some devices are reporting a size of 0x0mm:
    // https://github.com/JoseExposito/touchegg/issues/415
    if (getSizeStatus == 0 && widthMm != 0 && heightMm != 0) {
      tlg::info << "\tSize: " << widthMm << "mm x " << heightMm << "mm"
                << std::endl;

      tlg::info << "\tCalculating start_threshold and finish_threshold. "
                   "You can tune this values in your service file"
                << std::endl;

      if (hasGestureCap) {
        LininputDeviceHandler::calculateTouchpadThreshold(widthMm, heightMm,
                                                          info);
      } else {
        LininputDeviceHandler::calculateTouchscreenThreshold(widthMm, heightMm,
                                                             info);
      }
    } else {
      tlg::warning
          << "\tIt wasn't possible to get your device physical size, falling "
             "back to default start_threshold and finish_threshold. You can "
             "tune this values in your service file: "
             "https://github.com/JoseExposito/touchegg#daemon-configuration"
          << std::endl;
    }

    // User preferences override the thresholds
    if (this->startThreshold != -1) {
      info->startThreshold = this->startThreshold;
    }

    if (this->finishThreshold != -1) {
      info->finishThresholdHorizontal = this->finishThreshold;
      info->finishThresholdVertical = this->finishThreshold;
    }

    tlg::info << "\tstart_threshold: " << info->startThreshold << std::endl;
    tlg::info << "\tfinish_threshold_horizontal: "
              << info->finishThresholdHorizontal << std::endl;
    tlg::info << "\tfinish_threshold_vertical: "
              << info->finishThresholdVertical << std::endl;

    libinput_device_set_user_data(device, static_cast<void *>(info));
  }
}

void LininputDeviceHandler::calculateTouchpadThreshold(
    double widthMm, double heightMm, LibinputDeviceInfo *outInfo) {
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
  //  - start_threshold -> 1% or 5% of the maximum deltaX/Y
  //  - finish_threshold -> 9% or 40% of the maximum deltaX/Y
#ifdef LIBINPUT_FILTER_DELTAS
  constexpr int START_PERCENTAGE = 1;
  constexpr int FINISH_PERCENTAGE = 9;
#else
  constexpr int START_PERCENTAGE = 5;
  constexpr int FINISH_PERCENTAGE = 40;
#endif

  double minSize = std::min(widthMm, heightMm);
  outInfo->startThreshold =
      ((LininputDeviceHandler::mmToDpi(minSize) * START_PERCENTAGE) / 100);
  outInfo->finishThresholdHorizontal =
      ((LininputDeviceHandler::mmToDpi(widthMm) * FINISH_PERCENTAGE) / 100);
  outInfo->finishThresholdVertical =
      ((LininputDeviceHandler::mmToDpi(heightMm) * FINISH_PERCENTAGE) / 100);
}

double LininputDeviceHandler::mmToDpi(double mm) {
  constexpr double mmInOneInch = 25.4;  // 1 inch == 25.4 mm
  double inches = mm / mmInOneInch;
  double dpi = (inches * 1000);
  return dpi;
}

void LininputDeviceHandler::calculateTouchscreenThreshold(
    double widthMm, double heightMm, LibinputDeviceInfo *outInfo) {
  // start_threshold -> 2% of the width/height
  // finish_threshold -> 16% of the width/height
  constexpr int START_PERCENTAGE = 2;
  constexpr int FINISH_PERCENTAGE = 16;

  double minSize = std::min(widthMm, heightMm);
  outInfo->startThreshold = ((minSize * START_PERCENTAGE) / 100);
  outInfo->finishThresholdHorizontal = ((widthMm * FINISH_PERCENTAGE) / 100);
  outInfo->finishThresholdVertical = ((heightMm * FINISH_PERCENTAGE) / 100);
}

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
#ifndef GESTURE_GATHERER_LIBINPUT_GESTURE_GATHERER_H_
#define GESTURE_GATHERER_LIBINPUT_GESTURE_GATHERER_H_

#include <libinput.h>
#include <libudev.h>

#include <memory>

#include "gesture-gatherer/gesture-gatherer.h"
#include "gesture-gatherer/libinput-device-handler.h"
#include "gesture-gatherer/libinput-device-info.h"
#include "gesture-gatherer/libinput-pinch-handler.h"
#include "gesture-gatherer/libinput-swipe-handler.h"
#include "gesture-gatherer/libinput-touch-handler.h"
class Config;
class GestureControllerDelegate;
class LibinputGesture;

/**
 * Libinput backed GestureGatherer.
 */
class LibinputGestureGatherer : public GestureGatherer {
 public:
  LibinputGestureGatherer(GestureControllerDelegate *gestureController,
                          double startThreshold = -1,
                          double finishThreshold = -1);
  ~LibinputGestureGatherer();

  /**
   * Run libinput's event loop.
   */
  void run() override;

 private:
  /**
   * udev context.
   */
  struct udev *udevContext = nullptr;

  /**
   * libinput context.
   */
  struct libinput *libinputContext = nullptr;

  // Handlers
  LininputDeviceHandler deviceHandler;
  LininputSwipeHandler swipeHandler;
  LininputPinchHandler pinchHandler;
  LibinputTouchHandler touchHandler;

  /**
   * Handles the supported libinput events.
   */
  void handleEvent(struct libinput_event *event);

  /**
   * libinput structure with pointers to the open/close callbacks.
   */
  struct libinput_interface libinputInterface {
    LibinputGestureGatherer::openRestricted,
        LibinputGestureGatherer::closeRestricted
  };
  static int openRestricted(const char *path, int flags, void *userData);
  static void closeRestricted(int fd, void *userData);
};

#endif  // GESTURE_GATHERER_LIBINPUT_GESTURE_GATHERER_H_

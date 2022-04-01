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
#include "gesture-gatherer/libinput-gesture-gatherer.h"

#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "config/config.h"
#include "gesture-controller/gesture-controller-delegate.h"
#include "gesture/gesture-direction.h"
#include "utils/logger.h"

LibinputGestureGatherer::LibinputGestureGatherer(
    GestureControllerDelegate *gestureController, double startThreshold,
    double finishThreshold)
    : GestureGatherer(gestureController, startThreshold, finishThreshold),
      deviceHandler(gestureController, startThreshold, finishThreshold),
      swipeHandler(gestureController),
      pinchHandler(gestureController),
      touchHandler(gestureController) {
  this->udevContext = udev_new();
  if (this->udevContext == nullptr) {
    throw std::runtime_error{"Error initialising Touchégg: udev"};
  }

  this->libinputContext = libinput_udev_create_context(
      &this->libinputInterface, nullptr, this->udevContext);
  if (this->libinputContext == nullptr) {
    throw std::runtime_error{"Error initialising Touchégg: libinput"};
  }

  int seat = libinput_udev_assign_seat(this->libinputContext, "seat0");
  if (seat != 0) {
    throw std::runtime_error{"Error initialising Touchégg: libinput seat"};
  }
}

LibinputGestureGatherer::~LibinputGestureGatherer() {
  if (this->libinputContext != nullptr) {
    libinput_unref(this->libinputContext);
  }

  if (this->udevContext != nullptr) {
    udev_unref(this->udevContext);
  }
}

void LibinputGestureGatherer::run() {
  int fd = libinput_get_fd(this->libinputContext);
  if (fd == -1) {
    throw std::runtime_error{"Error initialising Touchégg: libinput_get_fd"};
  }

  // Create poll to wait until libinput's file descriptor has data
  // https://man7.org/linux/man-pages/man2/poll.2.html
  int pollTimeout = -1;
  std::array<struct pollfd, 1> pollFds{{fd, POLLIN, 0}};

  while (poll(pollFds.data(), pollFds.size(), pollTimeout) >= 0) {
    // Once the data is in the file descriptor, read and process every event
    bool hasEvents = true;
    do {
      libinput_dispatch(this->libinputContext);
      struct libinput_event *event = libinput_get_event(this->libinputContext);
      if (event != nullptr) {
        this->handleEvent(event);
      } else {
        hasEvents = false;
      }
    } while (hasEvents);
  }
}

void LibinputGestureGatherer::handleEvent(struct libinput_event *event) {
  libinput_event_type eventType = libinput_event_get_type(event);
  switch (eventType) {
    case LIBINPUT_EVENT_DEVICE_ADDED:
      this->deviceHandler.handleDeviceAdded(event);
      break;

    case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
      this->swipeHandler.handleSwipeBegin(event);
      break;
    case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE:
      this->swipeHandler.handleSwipeUpdate(event);
      break;
    case LIBINPUT_EVENT_GESTURE_SWIPE_END:
      this->swipeHandler.handleSwipeEnd(event);
      break;

    case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
      this->pinchHandler.handlePinchBegin(event);
      break;
    case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE:
      this->pinchHandler.handlePinchUpdate(event);
      break;
    case LIBINPUT_EVENT_GESTURE_PINCH_END:
      this->pinchHandler.handlePinchEnd(event);
      break;

    case LIBINPUT_EVENT_TOUCH_DOWN:
      this->touchHandler.handleTouchDown(event);
      break;
    case LIBINPUT_EVENT_TOUCH_UP:
    case LIBINPUT_EVENT_TOUCH_CANCEL:
      this->touchHandler.handleTouchUp(event);
      break;
    case LIBINPUT_EVENT_TOUCH_MOTION:
      this->touchHandler.handleTouchMotion(event);
      break;

    default:
      break;
  }

  libinput_event_destroy(event);
}

int LibinputGestureGatherer::openRestricted(const char *path, int flags,
                                            void * /*userData*/) {
  int fd = open(path, flags);  // NOLINT
  if (fd < 0) {
    tlg::warning << "Warning: Error opening device " << path << std::endl;
    return -errno;
  }
  return fd;
}

void LibinputGestureGatherer::closeRestricted(int fd, void * /*userData*/) {
  close(fd);
}

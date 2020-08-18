/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#include "gestures/gesture-gatherer.h"

#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <exception>
#include <iostream>

#include "config/config.h"

GestureGatherer::GestureGatherer(const Config &config) : config(config) {
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

GestureGatherer::~GestureGatherer() {
  if (this->libinputContext != nullptr) {
    libinput_unref(this->libinputContext);
  }

  if (this->udevContext != nullptr) {
    udev_unref(this->udevContext);
  }
}

void GestureGatherer::run() {
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
        // std::cout << libinput_event_get_type(event) << std::endl;
        libinput_event_destroy(event);
      } else {
        hasEvents = false;
      }
    } while (hasEvents);
  }
}

int GestureGatherer::openRestricted(const char *path, int flags,
                                    void * /*userData*/) {
  int fd = open(path, flags);  // NOLINT
  if (fd < 0) {
    throw std::runtime_error{
        "Error initialising Touchégg: libinput open.\n"
        "Please execute the following command:\n"
        "$ sudo usermod -a -G input $USER\n"
        "And reboot to solve this issue"};
  }
  return fd;
}

void GestureGatherer::closeRestricted(int fd, void * /*userData*/) {
  close(fd);
}

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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "config/config.h"

GestureGatherer::GestureGatherer(const Config &config) : config(config) {
  libinput_interface libinputInterface{GestureGatherer::openRestricted,
                                       GestureGatherer::closeRestricted};

  udev *udev = udev_new();
  if (udev == nullptr) {
    // TODO(jose) Throw an exception
  }

  libinput *libinput =
      libinput_udev_create_context(&libinputInterface, nullptr, udev);
  if (libinput == nullptr) {
    // TODO(jose) Throw an exception
  }

  int seat = libinput_udev_assign_seat(libinput, "seat0");
  if (seat != 0) {
    // TODO(jose) Throw an exception
  }
}

int GestureGatherer::openRestricted(const char *path, int flags,
                                    void *userData) {  // NOLINT
  int fd = open(path, flags);                          // NOLINT
  if (fd < 0) {
    // TODO(jose) Throw an exception
  }
  return fd;
}

void GestureGatherer::closeRestricted(int fd, void *userData) {  // NOLINT
  close(fd);
}

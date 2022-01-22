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
#include "utils/client-lock.h"

#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

#include <exception>
#include <stdexcept>
#include <string>

#include "utils/paths.h"

ClientLock::ClientLock(const std::string &lockInstance) {
  Paths::createUserConfigDir();

  std::filesystem::path lockPath = Paths::getUserLockFilePath(lockInstance);
  this->fd = open(lockPath.c_str(), O_CREAT | O_RDWR, 0640);  // NOLINT

  std::string errorMessage{
      "Another instance of Touchégg is already running. If you are sure that "
      "Touchégg is not already running, delete the lock file with the "
      "following command and try again:\n$ rm " +
      lockPath.string()};

  if (this->fd < 0) {
    throw std::runtime_error{errorMessage};
  }

  if (flock(this->fd, LOCK_EX | LOCK_NB) < 0) {
    close(this->fd);
    throw std::runtime_error{errorMessage};
  }
}

ClientLock::~ClientLock() {
  flock(this->fd, LOCK_UN);
  close(this->fd);
}

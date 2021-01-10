/**
 * Copyright 2011 - 2021 José Expósito <jose.exposito89@gmail.com>
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
#include "actions/maximize-restore-window.h"

#include <memory>

#include "animations/maximize-window-animation.h"
#include "animations/restore-window-animation.h"

void MaximizeRestoreWindow::onGestureBegin(const Gesture& /*gesture*/) {
  if (this->settings.count("fullscreen") == 1) {
    this->fullscreen = this->settings.at("fullscreen") == "true";
  }

  if (this->animate) {
    bool restoreWindowAnimation =
        this->fullscreen ? this->windowSystem.isWindowFullscreen(this->window)
                         : this->windowSystem.isWindowMaximized(this->window);
    if (restoreWindowAnimation) {
      this->animation = std::make_unique<RestoreWindowAnimation>(
          this->windowSystem, this->window, this->color, this->borderColor);
    } else {
      this->animation = std::make_unique<MaximizeWindowAnimation>(
          this->windowSystem, this->window, this->color, this->borderColor);
    }
  }
}

void MaximizeRestoreWindow::executeAction(const Gesture& /*gesture*/) {
  if (this->fullscreen) {
    this->windowSystem.toggleFullscreenWindow(this->window);
  } else {
    this->windowSystem.maximizeOrRestoreWindow(this->window);
  }
}

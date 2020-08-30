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
#include "actions/maximize-restore-window.h"

#include <utility>

#include "animations/maximize-window-animation.h"
#include "animations/restore-window-animation.h"

void MaximizeRestoreWindow::onGestureBegin(const Gesture& /*gesture*/) {
  bool animate = true;
  if (this->settings.count("animate") == 1) {
    animate = this->settings.at("animate") == "true";
  }

  // TODO(jose) Ignore system windows:
  // https://github.com/JoseExposito/touchegg/blob/master/src/touchegg/actions/implementation/ResizeWindow.cpp

  // TODO(jose) Allow to change the animation color??
  if (animate) {
    if (this->windowSystem.isWindowMaximized(this->window)) {
      this->animation = std::make_unique<RestoreWindowAnimation>(
          this->windowSystem, this->window);
    } else {
      this->animation = std::make_unique<MaximizeWindowAnimation>(
          this->windowSystem, this->window);
    }
  }
}

void MaximizeRestoreWindow::onGestureUpdate(const Gesture& gesture) {
  if (this->animation &&
      gesture.elapsedTime() >
          std::stoull(this->config.getGlobalSetting("animation_delay"))) {
    this->animation->render(gesture.percentage());
  }
}

void MaximizeRestoreWindow::onGestureEnd(const Gesture& gesture) {
  if (!this->animation ||
      gesture.percentage() > std::stoi(this->config.getGlobalSetting(
                                 "action_execute_threshold"))) {
    this->windowSystem.maximizeOrRestoreWindow(this->window);
  }
}

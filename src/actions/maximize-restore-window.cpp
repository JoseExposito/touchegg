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

#include <iostream>
#include <utility>

#include "animations/resize-window-animation.h"

void MaximizeRestoreWindow::onGestureBegin(const Gesture& /*gesture*/) {
  std::cout << "### MaximizeRestoreWindow::onGestureBegin ###" << std::endl;

  // TODO(jose) Check if animation is configured in this->settings
  this->animation = std::make_unique<ResizeWindowAnimation>(this->windowSystem);
}

void MaximizeRestoreWindow::onGestureUpdate(const Gesture& gesture) {
  // std::cout << "### MaximizeRestoreWindow::onGestureUpdate ###" << std::endl;

  if (this->animation) {
    std::cout << gesture.percentage() << std::endl;
    this->animation->render(gesture.percentage());
  }
}

void MaximizeRestoreWindow::onGestureEnd(const Gesture& gesture) {
  if (!this->animation || (this->animation && gesture.percentage() > 50)) {
    this->windowSystem.maximizeOrRestoreWindow(this->window);
  }
}

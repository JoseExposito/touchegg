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
#include "actions/close-window.h"

#include <memory>

#include "animations/close-window-animation.h"

void CloseWindow::onGestureBegin(const Gesture& /*gesture*/) {
  if (this->animate) {
    this->animation = std::make_unique<CloseWindowAnimation>(
        this->windowSystem, this->window, this->color, this->borderColor);
  }
}

void CloseWindow::executeAction(const Gesture& /*gesture*/) {
  this->windowSystem.closeWindow(this->window);
}

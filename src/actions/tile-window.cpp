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
#include "actions/tile-window.h"

#include "animations/animation-factory.h"

void TileWindow::onGestureBegin(const Gesture& /*gesture*/) {
  if (this->settings.count("direction") == 1) {
    this->toTheLeft = this->settings.at("direction") == "left";
  }

  if (this->animate) {
    AnimationType animationType = this->toTheLeft
                                      ? AnimationType::TILE_WINDOW_LEFT
                                      : AnimationType::TILE_WINDOW_RIGHT;

    this->animation = AnimationFactory::buildAnimation(
        animationType, this->windowSystem, this->window, this->color,
        this->borderColor);
  }
}

void TileWindow::executeAction(const Gesture& /*gesture*/) {
  this->windowSystem.tileWindow(this->window, this->toTheLeft);
}

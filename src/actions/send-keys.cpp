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
#include "actions/send-keys.h"

#include "animations/animation-factory.h"
#include "utils/string.h"

void SendKeys::onGestureBegin(const Gesture& gesture) {
  RepeatedAction::onGestureBegin(gesture);

  if (!this->animate) {
    return;
  }

  if (this->settings.count("animation") == 1) {
    std::string animationTypeStr = this->settings.at("animation");
    AnimationType animationType = animationTypeFromStr(animationTypeStr);

    this->animation = AnimationFactory::buildAnimation(
        animationType, this->windowSystem, this->window, this->color,
        this->borderColor);
  }
}

void SendKeys::executePrelude() {
  if (this->settings.count("modifiers") == 1) {
    this->modifiers = split(this->settings.at("modifiers"), '+');
  }

  if (this->settings.count("keys") == 1) {
    this->keys = split(this->settings.at("keys"), '+');
  }

  if (this->settings.count("decreaseKeys") == 1) {
    this->decreaseKeys = split(this->settings.at("decreaseKeys"), '+');
  }

  // Only the active window receives shortcuts
  if (!this->windowSystem.isSystemWindow(this->window)) {
    this->windowSystem.activateWindow(this->window);
  }

  // "Press" the modifiers and keys if required
  this->windowSystem.sendKeys(this->modifiers, true);
}

void SendKeys::executePostlude() {
  // "Release" the modifiers and keys if required
  this->windowSystem.sendKeys(this->modifiers, false);
}

void SendKeys::executeAction(const Gesture& /*gesture*/) {
  this->windowSystem.sendKeys(this->keys, true);
  this->windowSystem.sendKeys(this->keys, false);
}

void SendKeys::executeReverse(const Gesture& /*gesture*/) {
  this->windowSystem.sendKeys(this->decreaseKeys, true);
  this->windowSystem.sendKeys(this->decreaseKeys, false);
}

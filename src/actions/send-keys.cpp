/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
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

#include "utils/string.h"

void SendKeys::onGestureBegin(const Gesture& /*gesture*/) {
  if (this->settings.count("modifiers") == 1) {
    this->modifiers = split(this->settings.at("modifiers"), '+');
  }

  if (this->settings.count("keys") == 1) {
    this->keys = split(this->settings.at("keys"), '+');
  }

  if (this->settings.count("decreaseKeys") == 1) {
    this->decreaseKeys = split(this->settings.at("decreaseKeys"), '+');
  }

  if (this->settings.count("repeat") == 1) {
    this->repeat = (this->settings.at("repeat") == "true");
  }

  if (this->settings.count("on") == 1) {
    this->onBegin = (this->settings.at("on") == "begin");
  }

  // Only the active window receives shortcuts
  this->windowSystem.activateWindow(this->window);

  // "Press" the modifiers and keys if required
  this->windowSystem.sendKeys(this->modifiers, true);

  if (!this->repeat && this->onBegin) {
    this->windowSystem.sendKeys(this->keys, true);
    this->windowSystem.sendKeys(this->keys, false);
  }
}

void SendKeys::onGestureUpdate(const Gesture& gesture) {
  if (this->repeat) {
    constexpr int step = 10;
    bool increased = (gesture.percentage() >= (this->repeatPercentage + step));
    bool decreased = (gesture.percentage() <= (this->repeatPercentage - step));

    if (increased) {
      this->windowSystem.sendKeys(this->keys, true);
      this->windowSystem.sendKeys(this->keys, false);
      this->repeatPercentage += step;
    }

    if (decreased) {
      this->windowSystem.sendKeys(this->decreaseKeys, true);
      this->windowSystem.sendKeys(this->decreaseKeys, false);
      this->repeatPercentage -= step;
    }
  }
}

void SendKeys::onGestureEnd(const Gesture& /*gesture*/) {
  if (!this->repeat && !this->onBegin) {
    this->windowSystem.sendKeys(this->keys, true);
    this->windowSystem.sendKeys(this->keys, false);
  }

  this->windowSystem.sendKeys(this->modifiers, false);
}

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
#include "actions/run-command.h"

#include <cstdlib>

void RunCommand::onGestureBegin(const Gesture& /*gesture*/) {
  if (this->settings.count("command") == 1) {
    this->command = this->settings.at("command");
  }

  if (this->settings.count("decreaseCommand") == 1) {
    this->decreaseCommand = this->settings.at("decreaseCommand");
  }

  if (this->settings.count("repeat") == 1) {
    this->repeat = (this->settings.at("repeat") == "true");
  }

  if (this->settings.count("on") == 1) {
    this->onBegin = (this->settings.at("on") == "begin");
  }

  if (!this->repeat && this->onBegin) {
    system(this->command.c_str());
  }
}

void RunCommand::onGestureUpdate(const Gesture& gesture) {
  if (this->repeat) {
    constexpr int step = 10;
    bool increased = (gesture.percentage() >= (this->repeatPercentage + step));
    bool decreased = (gesture.percentage() <= (this->repeatPercentage - step));

    if (increased) {
      system(this->command.c_str());
      this->repeatPercentage += step;
    }

    if (decreased) {
      system(this->decreaseCommand.c_str());
      this->repeatPercentage -= step;
    }
  }
}

void RunCommand::onGestureEnd(const Gesture& /*gesture*/) {
  if (!this->repeat && !this->onBegin) {
    system(this->command.c_str());
  }
}

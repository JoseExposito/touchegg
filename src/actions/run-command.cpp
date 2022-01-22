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
#include "actions/run-command.h"

#include <cstdlib>

#include "animations/animation-factory.h"

void RunCommand::onGestureBegin(const Gesture& gesture) {
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

void RunCommand::executePrelude() {
  if (this->settings.count("command") == 1) {
    this->command = this->settings.at("command");
  }

  if (this->settings.count("decreaseCommand") == 1) {
    this->decreaseCommand = this->settings.at("decreaseCommand");
  }
}

void RunCommand::executeAction(const Gesture& /*gesture*/) {
  RunCommand::runCommand(this->command);
}

void RunCommand::executeReverse(const Gesture& /*gesture*/) {
  RunCommand::runCommand(this->decreaseCommand);
}

bool RunCommand::runCommand(const std::string& command) {
  int ret = system(command.c_str());
  return (ret == 0);
}

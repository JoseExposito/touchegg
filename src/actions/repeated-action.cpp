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
#include "actions/repeated-action.h"

#include <algorithm>

void RepeatedAction::executePrelude() {}
void RepeatedAction::executePostlude() {}

void RepeatedAction::onGestureBegin(const Gesture &gesture) {
  // read repeated action settings
  if (this->settings.count("repeat") == 1) {
    this->repeat = (this->settings.at("repeat") == "true");
  }

  if (this->settings.count("times") == 1) {
    const int times = std::clamp(std::stoi(this->settings.at("times")), 2, 15);
    this->repeatPercentageStep = (100 / times);
  }

  if (this->settings.count("on") == 1) {
    this->executeActionOn = executeActionOnFromStr(this->settings.at("on"));
  }

  // execute supplied prelude
  this->executePrelude();

  // run action on begin
  if (!this->repeat &&
      shouldExecuteAction(ExecuteActionOn::BEGIN, this->executeActionOn)) {
    this->executeAction(gesture);
  }
}

void RepeatedAction::onGestureUpdate(const Gesture &gesture) {
  AnimatedAction::onGestureUpdate(gesture);

  if (this->repeat) {
    const bool increased =
        (gesture.percentage() >=
         (this->repeatPercentage + this->repeatPercentageStep));
    const bool decreased =
        (gesture.percentage() <=
         (this->repeatPercentage - this->repeatPercentageStep));

    if (increased) {
      this->executeAction(gesture);
      this->repeatPercentage += this->repeatPercentageStep;
    }

    if (decreased) {
      this->executeReverse(gesture);
      this->repeatPercentage -= this->repeatPercentageStep;
    }
  }
}

void RepeatedAction::onGestureEnd(const Gesture &gesture) {
  if (!this->repeat &&
      shouldExecuteAction(ExecuteActionOn::END, this->executeActionOn)) {
    // Do not take into account the threshold is the action is executed on begin
    // and end. Otherwise, we could miss could execute only the on begin part.
    if (this->executeActionOn == ExecuteActionOn::BEGIN_AND_END ||
        gesture.percentage() >= this->threshold) {
      this->executeAction(gesture);
    }
  }

  this->executePostlude();
}

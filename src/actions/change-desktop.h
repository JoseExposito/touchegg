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
#ifndef ACTIONS_CHANGE_DESKTOP_H_
#define ACTIONS_CHANGE_DESKTOP_H_

#include "actions/action-direction.h"
#include "actions/animated-action.h"
#include "animations/animation-type.h"

/**
 * Action to change to the next or previous desktop.
 */
class ChangeDesktop : public AnimatedAction {
 public:
  using AnimatedAction::AnimatedAction;
  bool runOnSystemWindows() override { return true; }
  void onGestureBegin(const Gesture &gesture) override;
  void executeAction(const Gesture &gesture) override;

 private:
  ActionDirection direction = ActionDirection::AUTO;
  bool cyclic = false;

  ActionDirection getAnimationAutoDirection(const Gesture &gesture) const;
  ActionDirection getActionAutoDirection(const Gesture &gesture) const;
  static AnimationType directionToAnimation(ActionDirection direction);
};

#endif  // ACTIONS_CHANGE_DESKTOP_H_

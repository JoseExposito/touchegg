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
#ifndef ACTIONS_REPEATED_ACTION_H_
#define ACTIONS_REPEATED_ACTION_H_

#include "actions/animated-action.h"

class RepeatedAction : public AnimatedAction {
 public:
  using AnimatedAction::AnimatedAction;
  virtual ~RepeatedAction() = default;

  /**
   * Execute gesture on begin
   */
  void onGestureBegin(const Gesture &gesture) override;

  /**
   * Execute gesture repeatedly
   */
  void onGestureUpdate(const Gesture &gesture) override;

  /**
   * Execute gesture on end if threshold passed
   */
  void onGestureEnd(const Gesture &gesture) override;

  /**
   * If your action requires some pre-setup, override this method. This is
   * executed unconditionally upon gesture beginning
   */
  virtual void executePrelude();

  /**
   * If your action requires some post-setup, override this method. This is
   * executed unconditionally upon gesture ending
   */
  virtual void executePostlude();

  /**
   * Override this method to configure what is executed for succesful gesture
   * @param gesture The gesture that triggered the action
   */
  virtual void executeAction(const Gesture &gesture) = 0;

  /**
   * Override this method to configure what is executed for reversed gesture
   * @param gesture The gesture that triggered the action
   */
  virtual void executeReverse(const Gesture &gesture) = 0;

 protected:
  /**
   * Whether the action should be repeated or not.
   */
  bool repeat = false;

  /**
   * If "repeat" is true, the total gesture percentage accumulated.
   */
  double repeatPercentage = 0;

  /**
   * If "repeat" is true, the percentage that should be accumulated to execute
   * the action.
   */
  double repeatPercentageStep = 10;

  /**
   * Whether the action should be executed on gesture begin or end.
   */
  bool onBegin = true;
};

#endif  // ACTIONS_REPEATED_ACTION_H_

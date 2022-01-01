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
#ifndef ACTIONS_SEND_KEYS_H_
#define ACTIONS_SEND_KEYS_H_

#include <string>
#include <vector>

#include "actions/repeated-action.h"

/**
 * Action to emulate a shortcut.
 */
class SendKeys : public RepeatedAction {
 public:
  using RepeatedAction::RepeatedAction;
  void onGestureBegin(const Gesture &gesture) override;
  bool runOnSystemWindows() override { return true; }
  void executePrelude() override;
  void executePostlude() override;
  void executeAction(const Gesture &gesture) override;
  void executeReverse(const Gesture &gesture) override;

 private:
  std::vector<std::string> modifiers;
  std::vector<std::string> keys;
  std::vector<std::string> decreaseKeys;
};

#endif  // ACTIONS_SEND_KEYS_H_

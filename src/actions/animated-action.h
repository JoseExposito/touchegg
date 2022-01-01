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
#ifndef ACTIONS_ANIMATED_ACTION_H_
#define ACTIONS_ANIMATED_ACTION_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "actions/action.h"
#include "animations/animation.h"
#include "utils/color.h"

/**
 * Base class for animated actions.
 */
class AnimatedAction : public Action {
 public:
  /**
   * Default constructor.
   * @see Action.
   */
  AnimatedAction(std::unordered_map<std::string, std::string> settings,
                 const WindowSystem &windowSystem, const WindowT &window,
                 const Config &config);
  virtual ~AnimatedAction() = default;

  /**
   * Override this method to configure the animation.
   */
  // virtual void onGestureBegin(const Gesture &gesture) = 0;

  /**
   * Run the animation.
   */
  void onGestureUpdate(const Gesture &gesture) override;

  /**
   * This method calls "executeAction" if the animation passed the configured
   * threshold.
   */
  void onGestureEnd(const Gesture &gesture) override;
  virtual void executeAction(const Gesture &gesture) = 0;

 protected:
  /**
   * The animation to show.
   */
  std::unique_ptr<Animation> animation = nullptr;

  /**
   * If we should show the animation or not.
   */
  bool animate = true;

  /**
   * Animation color.
   */
  Color color;

  /**
   * Animation border color.
   */
  Color borderColor;

  /**
   * "animation_delay" in global config.
   */
  uint64_t animationDelay;
};

#endif  // ACTIONS_ANIMATED_ACTION_H_

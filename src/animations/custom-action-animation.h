/**
 * Copyright 2011 - 2021 José Expósito <jose.exposito89@gmail.com>
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
#ifndef ANIMATIONS_CUSTOM_ACTION_ANIMATION_H_
#define ANIMATIONS_CUSTOM_ACTION_ANIMATION_H_

#include <actions/Script.h>

#include <string>

#include "actions/action-direction.h"
#include "animations/animation.h"
#include "utils/color.h"
#include "utils/rectangle.h"

class CustomActionAnimation : public Animation {
 public:
  using Animation::Animation;
  CustomActionAnimation(const WindowSystem &windowSystem,
                         const WindowT &window, Color color, Color borderColor,
                         ActionDirection animationPosition, std::optional<Script> script);
  void render(double percentage) override;
  std::optional<Script> script = script;

 private:
  Rectangle maxSize;
  Color color;
  Color borderColor;
  double angle;
};

#endif  // ANIMATIONS_CUSTOM_ACTION_ANIMATION_H_

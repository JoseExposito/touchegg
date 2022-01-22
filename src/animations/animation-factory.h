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
#ifndef ANIMATIONS_ANIMATION_FACTORY_H_
#define ANIMATIONS_ANIMATION_FACTORY_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "animations/animation-type.h"
#include "animations/animation.h"
#include "utils/color.h"

class AnimationFactory {
 public:
  static std::unique_ptr<Animation> buildAnimation(
      AnimationType type, const WindowSystem &windowSystem,
      const WindowT &window, Color color, Color borderColor);
};

#endif  // ANIMATIONS_ANIMATION_FACTORY_H_

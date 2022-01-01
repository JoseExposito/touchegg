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
#include "animations/animation.h"

#include <chrono>  // NOLINT

void Animation::onUpdate(double percentage) {
  constexpr uint64_t frameRate = (1000 / 30);

  // Discard draws that exceed the frame rate
  auto now = std::chrono::system_clock::now().time_since_epoch();
  uint64_t millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

  if (millis < (this->lastRenderTimestamp + frameRate)) {
    return;
  }
  this->lastRenderTimestamp = millis;

  // Rely on the base class for rendering the animation
  this->render(percentage);
}

double Animation::value(double initialValue, double targetValue,
                        double percentage) {
  return (((targetValue - initialValue) * percentage) / 100) + initialValue;
}

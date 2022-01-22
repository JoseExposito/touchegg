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
#ifndef ANIMATIONS_ANIMATION_H_
#define ANIMATIONS_ANIMATION_H_

#include <cairo.h>

#include <memory>

#include "window-system/cairo-surface.h"
#include "window-system/window-system.h"

/**
 * Base class form animations.
 */
class Animation {
 public:
  Animation(const WindowSystem &windowSystem, const WindowT &window)
      : windowSystem(windowSystem),
        window(window),
        cairoSurface(this->windowSystem.createCairoSurface()) {}

  virtual ~Animation() = default;

  /**
   * Called every time an action request an update.
   * Decide if rendering is required or not.
   */
  void onUpdate(double percentage);

  /**
   * Draw the animation on screen.
   * @param percentage A number between 0 and 100 indicating the percentage of
   * the animation.
   */
  virtual void render(double percentage) = 0;

 protected:
  const WindowSystem &windowSystem;
  const WindowT &window;
  std::unique_ptr<CairoSurface> cairoSurface;

  /**
   * Animation maximun alpha value.
   */
  static constexpr double MAX_ALPHA = 0.6;

  /**
   * Utility method to calculate the current animation value based on the
   * percentage of the gesture performed.
   * Animations are always linear, as they are 1:1 to the user's movement.
   * @param initialValue Animation start value.
   * @param targetValue Animation end value.
   * @param percentage Current animation percentage.
   * @returns The linear animation value at the specified percentage.
   */
  static double value(double initialValue, double targetValue,
                      double percentage);

 private:
  uint64_t lastRenderTimestamp = 0;
};

#endif  // ANIMATIONS_ANIMATION_H_

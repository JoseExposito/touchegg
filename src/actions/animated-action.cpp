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
#include "actions/animated-action.h"

#include <utility>

AnimatedAction::AnimatedAction(
    std::unordered_map<std::string, std::string> settings,
    const WindowSystem &windowSystem, const WindowT &window,
    const Config &config)
    : Action(std::move(settings), windowSystem, window, config) {
  this->animationDelay =
      std::stoull(this->config.getGlobalSetting("animation_delay"));

  if (this->settings.count("animate") == 1) {
    this->animate = this->settings.at("animate") == "true";
  }

  if (this->animate) {
    std::string color;
    std::string borderColor;

    if (this->config.hasGlobalSetting("color")) {
      color = this->config.getGlobalSetting("color");
    }

    if (this->config.hasGlobalSetting("borderColor")) {
      borderColor = this->config.getGlobalSetting("borderColor");
    }

    if (this->settings.count("color") == 1) {
      color = this->settings.at("color");
    }

    if (this->settings.count("borderColor") == 1) {
      borderColor = this->settings.at("borderColor");
    }

    if (!color.empty()) {
      this->color = Color{color, ColorType::BACKGROUND};
    }

    if (!borderColor.empty()) {
      this->borderColor = Color{borderColor, ColorType::BORDER};
    }
  }
}

void AnimatedAction::onGestureUpdate(const Gesture &gesture) {
  if (this->animation && gesture.elapsedTime() > this->animationDelay) {
    this->animation->onUpdate(gesture.percentage());
  }
}

void AnimatedAction::onGestureEnd(const Gesture &gesture) {
  if (!this->animate || gesture.percentage() >= this->threshold) {
    this->executeAction(gesture);
  }
}

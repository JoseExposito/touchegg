/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#include "gesture-controller/gesture-controller.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

#include "actions/action-factory.h"
#include "actions/action-type.h"
#include "actions/action.h"
#include "config/config.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture-type.h"
#include "gesture/gesture.h"
#include "window-system/window-system.h"

GestureController::GestureController(const Config &config,
                                     const WindowSystem &windowSystem)
    : config(config), windowSystem(windowSystem) {}

void GestureController::onGestureBegin(std::unique_ptr<Gesture> gesture) {
  std::cout << "onGestureBegin" << std::endl;

  this->window = this->windowSystem.getWindowUnderCursor();

  // TODO(jose) Check if there is a gesture configured for the window
  std::string className = this->windowSystem.getWindowClassName(*this->window);
  std::cout << className << std::endl;

  const std::string application = "All";
  const GestureType gestureType = gesture->type();
  int fingers = gesture->fingers();
  const GestureDirection direction = gesture->direction();

  bool hasAction = this->config.hasGestureConfig(application, gestureType,
                                                 fingers, direction);
  if (hasAction) {
    std::cout << "Action configured for this gesture" << std::endl;

    auto pair = this->config.getGestureConfig(application, gestureType, fingers,
                                              direction);
    ActionType actionType = pair.first;
    std::unordered_map<std::string, std::string> actionSettings = pair.second;

    this->action =
        ActionFactory::buildAction(actionType, std::move(actionSettings),
                                   this->windowSystem, *this->window);

    if (this->action != nullptr) {
      std::cout << "Starting action" << std::endl;
      this->action->onGestureBegin(*gesture);
    }

    // TODO(jose) TEST!
    if (actionType == ActionType::MAXIMIZE_RESTORE_WINDOW) {
      std::cout << "onGestureBegin" << std::endl;
      std::cout << "Fingers: " << gesture->fingers() << std::endl;
      std::cout << "Delta X: " << gesture->deltaX() << std::endl;
      std::cout << "Delta Y: " << gesture->deltaY() << std::endl;
      if (gesture->direction() == GestureDirection::UP) {
        std::cout << "UP" << std::endl;
      }
    }
  }
}

void GestureController::onGestureUpdate(std::unique_ptr<Gesture> gesture) {
  if (this->action) {
    this->action->onGestureUpdate(*gesture);

    // TODO(jose)
    // std::cout << "onGestureUpdate" << std::endl;
    // std::cout << "Fingers: " << gesture->fingers() << std::endl;
    // std::cout << "Delta X: " << gesture->deltaX() << std::endl;
    // std::cout << "Delta Y: " << gesture->deltaY() << std::endl;
    // if (gesture->direction() == GestureDirection::UP) {
    //   std::cout << "UP" << std::endl;
    // }
  }
}

void GestureController::onGestureEnd(std::unique_ptr<Gesture> gesture) {
  if (this->action) {
    this->action->onGestureEnd(*gesture);

    // TODO(jose)
    std::cout << "onGestureEnd" << std::endl;
    std::cout << "Fingers: " << gesture->fingers() << std::endl;
    std::cout << "Delta X: " << gesture->deltaX() << std::endl;
    std::cout << "Delta Y: " << gesture->deltaY() << std::endl;
    if (gesture->direction() == GestureDirection::UP) {
      std::cout << "UP" << std::endl;
    }
  }

  this->action.reset();
}

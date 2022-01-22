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
#include "gesture-controller/gesture-controller.h"

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
#include "utils/logger.h"
#include "window-system/window-system.h"

GestureController::GestureController(const Config &config,
                                     const WindowSystem &windowSystem)
    : config(config), windowSystem(windowSystem) {}

void GestureController::onGestureBegin(std::unique_ptr<Gesture> gesture) {
  tlg::debug << "Gesture begin detected" << std::endl;
  tlg::debug << "\tGesture information:" << std::endl;
  tlg::debug << "\t\tFingers: " << gesture->fingers() << std::endl;
  tlg::debug << "\t\tType: " << gestureTypeToStr(gesture->type()) << std::endl;
  tlg::debug << "\t\tDirection: " << gestureDirectionToStr(gesture->direction())
             << std::endl;

  this->rotatedDirection = this->windowSystem.calculateRotation(
      gesture->type(), gesture->performedOnDeviceType(), gesture->direction());
  if (this->rotatedDirection != gesture->direction()) {
    tlg::debug << "\t\tDirection after rotation: "
               << gestureDirectionToStr(this->rotatedDirection) << std::endl;
    gesture->setDirection(this->rotatedDirection);
  }

  this->window = this->windowSystem.getWindowUnderCursor();
  this->action = this->getActionForGesture(*gesture, *this->window);

  // Check if we should run the action
  bool isSystemWindow = this->windowSystem.isSystemWindow(*this->window);
  this->executeAction =
      (this->action != nullptr)  // Not nullptr action
      && (!isSystemWindow        // Not system window
                                 // The action can run on system windows:
          || (isSystemWindow && this->action->runOnSystemWindows()));

  if (!executeAction) {
    tlg::debug
        << "\tIgnoring this gesture. This could mean no action is configured, "
           "the configured action is not supported or that it was performed in "
           "a system window (panel, dock, desktop, etc)"
        << std::endl;
    return;
  }

  tlg::debug << "\tStarting action" << std::endl;
  this->action->onGestureBegin(*gesture);
}

void GestureController::onGestureUpdate(std::unique_ptr<Gesture> gesture) {
  if (this->executeAction) {
    tlg::debug << "Gesture update detected (" << gesture->percentage() << "%)"
               << std::endl;
    gesture->setDirection(this->rotatedDirection);
    this->action->onGestureUpdate(*gesture);
  }
}

void GestureController::onGestureEnd(std::unique_ptr<Gesture> gesture) {
  if (this->executeAction) {
    tlg::debug << "Gesture end detected" << std::endl;
    gesture->setDirection(this->rotatedDirection);
    this->action->onGestureEnd(*gesture);
  }

  this->action.reset();
  this->rotatedDirection = GestureDirection::UNKNOWN;
}

std::unique_ptr<Action> GestureController::getActionForGesture(
    const Gesture &gesture, const WindowT &window) const {
  bool hasAction = false;
  std::string application;
  const GestureType gestureType = gesture.type();
  int fingers = gesture.fingers();
  const GestureDirection direction = gesture.direction();

  // First check if there is an specific application gesture
  application = this->windowSystem.getWindowClassName(window);
  tlg::debug << "\tGesture performed on app: " << application << std::endl;
  hasAction = this->config.hasGestureConfig(application, gestureType, fingers,
                                            direction);

  // If no gesture was configured, check the global gestures
  if (!hasAction) {
    application = "All";
    hasAction = this->config.hasGestureConfig(application, gestureType, fingers,
                                              direction);
  }

  if (!hasAction) {
    tlg::debug << "\tNo action configured for this gesture" << std::endl;
    return nullptr;
  }

  tlg::debug << "\tAction configured for this gesture" << std::endl;

  auto pair = this->config.getGestureConfig(application, gestureType, fingers,
                                            direction);
  ActionType actionType = pair.first;
  std::unordered_map<std::string, std::string> actionSettings = pair.second;

  return ActionFactory::buildAction(actionType, std::move(actionSettings),
                                    this->windowSystem, *this->window,
                                    this->config);
}

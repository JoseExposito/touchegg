/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
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
#include "gesture-gatherer/libinput-touch-handler.h"

#include <iostream>

void LibinputTouchHandler::handleTouchDown(struct libinput_event *event) {
  if (!this->state.started) {
    this->state.fingers++;
  }

  std::cout << "DOWN " << this->state.fingers << std::endl;
  libinput_event_destroy(event);
}

void LibinputTouchHandler::handleTouchUp(struct libinput_event *event) {
  if (!this->state.started) {
    this->state.fingers++;
  } else {
    this->state.reset();
  }

  std::cout << "UP " << this->state.fingers << std::endl;
  libinput_event_destroy(event);
}

void LibinputTouchHandler::handleTouchMotion(struct libinput_event *event) {
  // std::cout << "MOTION" << std::endl;
  // TODO(jose) Store deltaX/Y
  libinput_event_destroy(event);
}

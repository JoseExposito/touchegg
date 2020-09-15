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
#include "gesture-gatherer/libinput-gesture-gatherer.h"

#include <fcntl.h>
#include <libinput.h>
#include <libudev.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <chrono>  // NOLINT
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <utility>

#include "config/config.h"
#include "gesture-controller/gesture-controller-delegate.h"
#include "gesture/gesture-direction.h"
#include "gesture/gesture.h"
#include "gesture/libinput-gesture.h"

LibinputGestureGatherer::LibinputGestureGatherer(
    const Config &config, GestureControllerDelegate *gestureController)
    : GestureGatherer(config, gestureController) {
  this->udevContext = udev_new();
  if (this->udevContext == nullptr) {
    throw std::runtime_error{"Error initialising Touchégg: udev"};
  }

  this->libinputContext = libinput_udev_create_context(
      &this->libinputInterface, nullptr, this->udevContext);
  if (this->libinputContext == nullptr) {
    throw std::runtime_error{"Error initialising Touchégg: libinput"};
  }

  int seat = libinput_udev_assign_seat(this->libinputContext, "seat0");
  if (seat != 0) {
    throw std::runtime_error{"Error initialising Touchégg: libinput seat"};
  }
}

LibinputGestureGatherer::~LibinputGestureGatherer() {
  if (this->libinputContext != nullptr) {
    libinput_unref(this->libinputContext);
  }

  if (this->udevContext != nullptr) {
    udev_unref(this->udevContext);
  }
}

void LibinputGestureGatherer::run() {
  int fd = libinput_get_fd(this->libinputContext);
  if (fd == -1) {
    throw std::runtime_error{"Error initialising Touchégg: libinput_get_fd"};
  }

  // Create poll to wait until libinput's file descriptor has data
  // https://man7.org/linux/man-pages/man2/poll.2.html
  int pollTimeout = -1;
  std::array<struct pollfd, 1> pollFds{{fd, POLLIN, 0}};

  while (poll(pollFds.data(), pollFds.size(), pollTimeout) >= 0) {
    // Once the data is in the file descriptor, read and process every event
    bool hasEvents = true;
    do {
      libinput_dispatch(this->libinputContext);
      struct libinput_event *event = libinput_get_event(this->libinputContext);
      if (event != nullptr) {
        this->handleEvent(event);
      } else {
        hasEvents = false;
      }
    } while (hasEvents);
  }
}

void LibinputGestureGatherer::handleEvent(struct libinput_event *event) {
  libinput_event_type eventType = libinput_event_get_type(event);
  switch (eventType) {
    case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
      this->handleSwipeBegin(std::make_unique<LibinputGesture>(event));
      break;
    case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE:
      this->handleSwipeUpdate(std::make_unique<LibinputGesture>(event));
      break;
    case LIBINPUT_EVENT_GESTURE_SWIPE_END:
      this->handleSwipeEnd(std::make_unique<LibinputGesture>(event));
      break;

    case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
      this->handlePinchBegin(std::make_unique<LibinputGesture>(event));
      break;
    case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE:
      this->handlePinchUpdate(std::make_unique<LibinputGesture>(event));
      break;
    case LIBINPUT_EVENT_GESTURE_PINCH_END:
      this->handlePinchEnd(std::make_unique<LibinputGesture>(event));
      break;

    default:
      libinput_event_destroy(event);
      break;
  }
}

void LibinputGestureGatherer::handleSwipeBegin(
    std::unique_ptr<LibinputGesture> /*gesture*/) {
  this->swipeState.reset();
}

void LibinputGestureGatherer::handleSwipeUpdate(
    std::unique_ptr<LibinputGesture> gesture) {
  this->swipeState.deltaX += gesture->deltaX();
  this->swipeState.deltaY += gesture->deltaY();

  if (!this->swipeState.started) {
    const double threshold =
        std::stod(this->config.getGlobalSetting("threshold"));

    if (std::abs(this->swipeState.deltaX) > threshold ||
        std::abs(this->swipeState.deltaY) > threshold) {
      this->swipeState.started = true;
      this->gestureStartTimestamp = this->getTimestamp();
      this->swipeState.direction = this->calculateSwipeDirection();
      this->swipeState.percentage = this->calculateSwipeAnimationPercentage();

      gesture->setPercentage(this->swipeState.percentage);
      gesture->setDirection(this->swipeState.direction);
      gesture->setElapsedTime(0);
      this->gestureController->onGestureBegin(std::move(gesture));
    }
  } else {
    this->swipeState.percentage = this->calculateSwipeAnimationPercentage();

    gesture->setPercentage(this->swipeState.percentage);
    gesture->setDirection(this->swipeState.direction);
    gesture->setElapsedTime(this->calculateElapsedTime());
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LibinputGestureGatherer::handleSwipeEnd(
    std::unique_ptr<LibinputGesture> gesture) {
  if (this->swipeState.started) {
    this->swipeState.percentage = this->calculateSwipeAnimationPercentage();

    gesture->setPercentage(this->swipeState.percentage);
    gesture->setDirection(this->swipeState.direction);
    gesture->setElapsedTime(this->calculateElapsedTime());
    this->gestureController->onGestureEnd(std::move(gesture));
  }

  this->swipeState.reset();
}

GestureDirection LibinputGestureGatherer::calculateSwipeDirection() const {
  if (std::abs(this->swipeState.deltaX) > std::abs(this->swipeState.deltaY)) {
    return (this->swipeState.deltaX > 0) ? GestureDirection::RIGHT
                                         : GestureDirection::LEFT;
  }

  return (this->swipeState.deltaY > 0) ? GestureDirection::DOWN
                                       : GestureDirection::UP;
}

int LibinputGestureGatherer::calculateSwipeAnimationPercentage() const {
  const double threshold =
      std::stod(this->config.getGlobalSetting("threshold"));
  const int deltaMax =
      std::stoi(this->config.getGlobalSetting("animation_finish_threshold"));

  int max = threshold + deltaMax;
  int current = 0;
  GestureDirection direction = this->swipeState.direction;

  switch (direction) {
    case GestureDirection::UP:
      current = std::abs(std::min(0.0, this->swipeState.deltaY + threshold));
      break;
    case GestureDirection::DOWN:
      current = std::max(0.0, this->swipeState.deltaY - threshold);
      break;
    case GestureDirection::LEFT:
      current = std::abs(std::min(0.0, this->swipeState.deltaX + threshold));
      break;
    case GestureDirection::RIGHT:
      current = std::max(0.0, this->swipeState.deltaX - threshold);
      break;
    default:
      break;
  }

  return std::min((current * 100) / max, 100);
}

void LibinputGestureGatherer::handlePinchBegin(
    std::unique_ptr<LibinputGesture> /*gesture*/) {
  this->pinchState.reset();
}

void LibinputGestureGatherer::handlePinchUpdate(
    std::unique_ptr<LibinputGesture> gesture) {
  if (!this->pinchState.started) {
    this->pinchState.started = true;
    this->gestureStartTimestamp = this->getTimestamp();
    this->pinchState.delta = gesture->radiusDelta();
    this->pinchState.direction = (this->pinchState.delta > 1)
                                     ? GestureDirection::OUT
                                     : GestureDirection::IN;
    this->pinchState.percentage = this->calculatePinchAnimationPercentage();

    gesture->setPercentage(this->pinchState.percentage);
    gesture->setDirection(this->pinchState.direction);
    gesture->setElapsedTime(0);
    this->gestureController->onGestureBegin(std::move(gesture));
  } else {
    this->pinchState.delta = gesture->radiusDelta();
    this->pinchState.percentage = this->calculatePinchAnimationPercentage();

    gesture->setPercentage(this->pinchState.percentage);
    gesture->setDirection(this->pinchState.direction);
    gesture->setElapsedTime(this->calculateElapsedTime());
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LibinputGestureGatherer::handlePinchEnd(
    std::unique_ptr<LibinputGesture> gesture) {
  if (this->pinchState.started) {
    this->pinchState.delta = gesture->radiusDelta();
    this->pinchState.percentage = this->calculatePinchAnimationPercentage();

    gesture->setPercentage(this->pinchState.percentage);
    gesture->setDirection(this->pinchState.direction);
    gesture->setElapsedTime(this->calculateElapsedTime());
    this->gestureController->onGestureEnd(std::move(gesture));
  }

  this->pinchState.reset();
}

int LibinputGestureGatherer::calculatePinchAnimationPercentage() const {
  // Delta starts at 1.0:
  // https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#pinch-gestures
  GestureDirection direction = this->pinchState.direction;
  double delta = this->pinchState.delta;

  // With direction IN, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 0.0.
  if (direction == GestureDirection::IN) {
    return std::min(100, static_cast<int>(std::abs(delta - 1.0) * 100));
  }

  // With direction OUT, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 2.0.
  if (direction == GestureDirection::OUT) {
    return std::min(
        100,
        static_cast<int>(std::max(0.0, this->pinchState.delta - 1.0) * 100));
  }

  return 0;
}

uint64_t LibinputGestureGatherer::getTimestamp() const {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  uint64_t millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
  return millis;
}

uint64_t LibinputGestureGatherer::calculateElapsedTime() const {
  return this->getTimestamp() - this->gestureStartTimestamp;
}

int LibinputGestureGatherer::openRestricted(const char *path, int flags,
                                            void * /*userData*/) {
  int fd = open(path, flags);  // NOLINT
  if (fd < 0) {
    throw std::runtime_error{
        "Error initialising Touchégg: libinput open.\n"
        "Please execute the following command:\n"
        "$ sudo usermod -a -G input $USER\n"
        "And reboot to solve this issue"};
  }
  return fd;
}

void LibinputGestureGatherer::closeRestricted(int fd, void * /*userData*/) {
  close(fd);
}

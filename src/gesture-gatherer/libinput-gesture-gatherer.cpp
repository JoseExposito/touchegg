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
    case LIBINPUT_EVENT_DEVICE_ADDED:
      this->handleDeviceAdded(event);
      break;

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

void LibinputGestureGatherer::handleDeviceAdded(
    struct libinput_event *event) const {
  struct libinput_device *device = libinput_event_get_device(event);
  if (libinput_device_has_capability(device, LIBINPUT_DEVICE_CAP_GESTURE) !=
      0) {
    std::cout << "Compatible device detected:" << std::endl;

    const char *name = libinput_device_get_name(device);
    std::cout << "\tName: " << name << std::endl;

    auto info = new LibinputDeviceInfo{};  // NOLINT

    double widthMm = 0;
    double heightMm = 0;
    if (libinput_device_get_size(device, &widthMm, &heightMm) == 0) {
      // From the official documentation:
      // https://wayland.freedesktop.org/libinput/doc/latest/normalization-of-relative-motion.html#motion-normalization
      //
      // libinput does partial normalization of relative input. For devices
      // with a resolution of 1000dpi and higher, motion events are
      // normalized to a default of 1000dpi before pointer acceleration is
      // applied.
      //
      // Touchpads may have a different resolution for the horizontal and
      // vertical axis. Interpreting coordinates from the touchpad without
      // taking resolution into account results in uneven motion.
      // libinput scales unaccelerated touchpad motion to the resolution of
      // the touchpad’s x axis, i.e. the unaccelerated value for the y axis
      // is: y = (x / resolution_x) * resolution_y.

      // Size is expressed in mm, but gesture deltaX/Y is normalized to
      // 1000dpi, thus, calculate how the maximum deltaX/Y and set:
      //  - threshold -> 2% of the maximum deltaX/Y
      //  - animation_finish_threshold -> 10% of the maximum deltaX/Y
      std::cout << "\tSize: " << widthMm << "mm x " << heightMm << "mm"
                << std::endl;

      std::cout << "\tCalculating threshold and animation_finish_threshold. "
                   "You can tune this values in your configuration file"
                << std::endl;

      double minSize = std::min(widthMm, heightMm);
      double inches = minSize / 25.4;  // 1 inch == 25.4 mm
      double dpi = (inches * 1000);
      info->threshold = ((2 * dpi) / 100);
      info->animationFinishThreshold = ((10 * dpi) / 100);
    } else {
      std::cout
          << "\tIt wasn't possible to get your device physical size, falling "
             "back to default threshold and animation_finish_threshold. You "
             "can tune this values in your configuration file"
          << std::endl;
    }

    std::cout << "\tthreshold: " << info->threshold << std::endl;
    std::cout << "\tanimation_finish_threshold: "
              << info->animationFinishThreshold << std::endl;

    libinput_device_set_user_data(device, static_cast<void *>(info));
  }
}

LibinputDeviceInfo LibinputGestureGatherer::getDeviceInfo(
    const LibinputGesture &gesture) const {
  LibinputDeviceInfo info;

  // Get the precalculated thresholds
  struct libinput_device *device = gesture.getDevice();
  void *userData = libinput_device_get_user_data(device);

  if (userData != nullptr) {
    auto aux = static_cast<LibinputDeviceInfo *>(userData);
    info.threshold = aux->threshold;
    info.animationFinishThreshold = aux->animationFinishThreshold;
  }

  // User preferences override the thresholds
  if (this->config.hasGlobalSetting("threshold")) {
    info.threshold = std::stod(this->config.getGlobalSetting("threshold"));
  }

  if (this->config.hasGlobalSetting("animation_finish_threshold")) {
    info.animationFinishThreshold =
        std::stod(this->config.getGlobalSetting("animation_finish_threshold"));
  }

  return info;
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
    LibinputDeviceInfo info = this->getDeviceInfo(*gesture);

    if (std::abs(this->swipeState.deltaX) > info.threshold ||
        std::abs(this->swipeState.deltaY) > info.threshold) {
      this->swipeState.started = true;
      this->gestureStartTimestamp = this->getTimestamp();
      this->swipeState.direction = this->calculateSwipeDirection();
      this->swipeState.percentage =
          this->calculateSwipeAnimationPercentage(*gesture);

      gesture->setPercentage(this->swipeState.percentage);
      gesture->setDirection(this->swipeState.direction);
      gesture->setElapsedTime(0);
      this->gestureController->onGestureBegin(std::move(gesture));
    }
  } else {
    this->swipeState.percentage =
        this->calculateSwipeAnimationPercentage(*gesture);

    gesture->setPercentage(this->swipeState.percentage);
    gesture->setDirection(this->swipeState.direction);
    gesture->setElapsedTime(this->calculateElapsedTime());
    this->gestureController->onGestureUpdate(std::move(gesture));
  }
}

void LibinputGestureGatherer::handleSwipeEnd(
    std::unique_ptr<LibinputGesture> gesture) {
  if (this->swipeState.started) {
    this->swipeState.percentage =
        this->calculateSwipeAnimationPercentage(*gesture);

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

int LibinputGestureGatherer::calculateSwipeAnimationPercentage(
    const LibinputGesture &gesture) const {
  LibinputDeviceInfo info = this->getDeviceInfo(gesture);
  double threshold = info.threshold;
  double animationFinishThreshold = info.animationFinishThreshold;

  int max = threshold + animationFinishThreshold;
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
  // delta is 0.0
  if (direction == GestureDirection::IN) {
    return std::min(100, static_cast<int>(std::abs(delta - 1.0) * 100));
  }

  // With direction OUT, 0% is returned when the delta is 1.0 and 100% when the
  // delta is 2.0
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
        "Touchégg should be run in daemon mode by systemd in order to be part "
        "of the 'input' group and have access to your touchpad.\n"
        "If you prefer to run Touchégg in a single process (touchegg --all) "
        "without using systemd, please execute the following command:\n"
        "$ sudo usermod -a -G input $USER\n"
        "And reboot to solve this issue"};
  }
  return fd;
}

void LibinputGestureGatherer::closeRestricted(int fd, void * /*userData*/) {
  close(fd);
}

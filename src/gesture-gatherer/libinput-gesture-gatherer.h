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
#ifndef GESTURE_GATHERER_LIBINPUT_GESTURE_GATHERER_H_
#define GESTURE_GATHERER_LIBINPUT_GESTURE_GATHERER_H_

#include <libinput.h>
#include <libudev.h>

#include <memory>

#include "gesture-gatherer/gesture-gatherer.h"
#include "gesture-gatherer/libinput-pinch-state.h"
#include "gesture-gatherer/libinput-swipe-state.h"
class Config;
class GestureControllerDelegate;
class LibinputGesture;

/**
 * Libinput backed GestureGatherer.
 */
class LibinputGestureGatherer : public GestureGatherer {
 public:
  LibinputGestureGatherer(const Config &config,
                          GestureControllerDelegate *gestureController);
  ~LibinputGestureGatherer();

  /**
   * Run libinput's event loop.
   */
  void run() override;

 private:
  /**
   * udev context.
   */
  struct udev *udevContext = nullptr;

  /**
   * libinput context.
   */
  struct libinput *libinputContext = nullptr;

  /**
   * Epoch time in milliseconds at the start of the gesture.
   */
  uint64_t gestureStartTimestamp = 0;

  /**
   * Required data to handle swipes.
   */
  LibinputSwipeState swipeState;

  /**
   * Required data to handle pinchs.
   */
  LibinputPinchState pinchState;

  /**
   * Handles the supported libinput events.
   */
  void handleEvent(struct libinput_event *event);

  /**
   * When the user starts a swipe, we still don't know the direction, so here we
   * just reset this->swipeState.
   * @param gesture Libinput specialized gesture.
   */
  void handleSwipeBegin(std::unique_ptr<LibinputGesture> gesture);

  /**
   * On every update we increase or decrease "this->swipeState.deltaX" and
   * "this->swipeState.deltaY". Once any of them passes the configured threshold
   * we send a begin event to the GestureControllerDelegate. Once the threshold
   * is passed we send update events to the GestureControllerDelegate until the
   * gesture ends.
   * @param gesture Libinput specialized gesture.
   */
  void handleSwipeUpdate(std::unique_ptr<LibinputGesture> gesture);

  /**
   * Send a end event to the GestureControllerDelegate if a gesture was
   * detected.
   * If the gesture didn't pass the threshold we should not notify it.
   * @param gesture Libinput specialized gesture.
   */
  void handleSwipeEnd(std::unique_ptr<LibinputGesture> gesture);

  /**
   * @returns The direction of a swipe gesture.
   */
  GestureDirection calculateSwipeDirection() const;

  /**
   * @returns The percentage (between 0 and 100) of the gesture animation.
   */
  int calculateSwipeAnimationPercentage() const;

  /**
   * When the user starts a pinch, we still don't know the direction, so here we
   * just reset this->swipeState.
   * @param gesture Libinput specialized gesture.
   */
  void handlePinchBegin(std::unique_ptr<LibinputGesture> gesture);
  void handlePinchUpdate(std::unique_ptr<LibinputGesture> gesture);
  void handlePinchEnd(std::unique_ptr<LibinputGesture> gesture);

  /**
   * @returns The percentage (between 0 and 100) of the gesture animation.
   */
  int calculatePinchAnimationPercentage() const;

  /**
   * @returns The current epoch time in milliseconds.
   */
  uint64_t getTimestamp() const;

  /**
   * @return Elapsed milliseconds since the beginning of the gesture.
   */
  uint64_t calculateElapsedTime() const;

  /**
   * libinput structure with pointers to the open/close callbacks.
   */
  struct libinput_interface libinputInterface {
    LibinputGestureGatherer::openRestricted,
        LibinputGestureGatherer::closeRestricted
  };
  static int openRestricted(const char *path, int flags, void *userData);
  static void closeRestricted(int fd, void *userData);
};

#endif  // GESTURE_GATHERER_LIBINPUT_GESTURE_GATHERER_H_

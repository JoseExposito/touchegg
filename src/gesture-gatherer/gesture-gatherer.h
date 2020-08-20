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
#ifndef GESTURE_GATHERER_GESTURE_GATHERER_H_
#define GESTURE_GATHERER_GESTURE_GATHERER_H_

class Config;
class GestureControllerDelegate;

/**
 * A GestureGatherer is in charge of gathering the gestures performed by the
 * user and sending them to the GestureController.
 *
 * In this way, the underlying driver used to gather those gestures is
 * abstracted from the rest of the program, allowing to easily support multiple
 * backends.
 *
 * This abstract class is the interface every GestureGatherer must implement.
 */
class GestureGatherer {
 public:
  /**
   * Default contructor.
   * @param config Object to access the configuration.
   * @param gestureController GestureController where the GestureGatherer will
   * send the gestures.
   */
  GestureGatherer(const Config &config,
                  const GestureControllerDelegate &gestureController)
      : config(config), gestureController(gestureController) {}

  virtual ~GestureGatherer() = default;

  /**
   * Run the GestureGatherer event loop.
   */
  virtual void run() = 0;

 protected:
  const Config &config;

  const GestureControllerDelegate &gestureController;
};

#endif  // GESTURE_GATHERER_GESTURE_GATHERER_H_

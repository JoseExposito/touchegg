# Changelog

## 2.0.14 - 2022-04-02

  - New COPR URL:

    https://copr.fedorainfracloud.org/coprs/joseexposito/touchegg/

  - Performance improvements calculating the size of the animations

    https://github.com/JoseExposito/touchegg/pull/564

  - Fix crash that might happen when multiple input devices are added and removed

    https://github.com/JoseExposito/touchegg/issues/566

## 2.0.13 - 2022-01-08

  - Improve pinch detection when the fingers are placed horizontally or vertically

    https://github.com/JoseExposito/touchegg/issues/541

  - Allow to run in multiple X displays

    https://github.com/JoseExposito/touchegg/issues/538

  - Allow to configure the number of times a repeated action is executed

    https://github.com/JoseExposito/touchegg/issues/553


## 2.0.12 - 2021-10-21

  - Improve pinch gesture detection on touchscreens

    https://github.com/JoseExposito/touchegg/issues/524

  - Honor the XDG basedir specification

    https://github.com/JoseExposito/touchegg/issues/525


## 2.0.11 - 2021-07-05

New:

  - Allow to display any animation on SEND_KEYS/RUN_COMMAND

    https://github.com/JoseExposito/touchegg/issues/505

  - Add cyclic option to CHANGE_DESKTOP

    https://github.com/JoseExposito/touchegg/issues/502

  - Packages for CentOS (EPEL), Fedora and openSUSE available on COPR

    https://copr.fedorainfracloud.org/coprs/jose_exposito/touchegg/


## 2.0.10 - 2021-06-07

New:

  - Add Void Linux install instructions
  - Add Artix Linux install instructions

Improvements:

  - Touchscreen: Use touch average to calculate deltas

    https://github.com/JoseExposito/touchegg/issues/499

  - Simplify the build process in distros that don't support systemd

    https://github.com/JoseExposito/touchegg/issues/481

Fix:

  - libinput 1.18 support: Different deltas depending on libinput version

    https://github.com/JoseExposito/touchegg/issues/489


## 2.0.9 - 2021-04-05

New:

  - Use screen rotation to calculate touchscreen gestures direction

    https://github.com/JoseExposito/touchegg/issues/459

Improvements:

  - Build the RPM package as part of the CI process improving its compatibility

    https://github.com/JoseExposito/touchegg/issues/475


## 2.0.8 - 2021-02-24

New:

  - Added daily and stable PPA builds

    https://launchpad.net/~touchegg/+archive/ubuntu/stable

Fixed:

  - Fix animation when screens ot the same size are arranged vertically

    https://github.com/JoseExposito/touchegg/issues/447

  - Fix crash caused by a g_variant not being referenced

    https://github.com/JoseExposito/touchegg/issues/449

  - Handle the TOUCH_CANCEL event to avoid bugs

    https://github.com/JoseExposito/touchegg/issues/458


## 2.0.7 - 2021-02-07

New:

  - Release Touché, a configuration GUI

    https://github.com/JoseExposito/touche

    https://github.com/JoseExposito/touchegg/issues/340

  - Include different log levels, thanks to @imabuddha

    https://github.com/JoseExposito/touchegg/issues/431

Improvements:

  - Improvements in documentation

Fixed:

  - Fix intermittent crash

    https://github.com/JoseExposito/touchegg/issues/443

## 2.0.6 - 2021-02-01

New:

  - New action added: `FULLSCREEN_WINDOW`. Thanks to @MarioJim

    https://github.com/JoseExposito/touchegg/issues/440

Improvements:

  - Use D-Bus for daemon-client communication, making easier to write clients different languages

    https://github.com/JoseExposito/touchegg/issues/436

  - Animations are pixel-precise at low speeds

    https://github.com/JoseExposito/touchegg/issues/434

  - Make application name case insensitive in config file

    https://github.com/JoseExposito/touchegg/issues/432

## 2.0.5 - 2021-01-05

New:

  - Allow to cancel non animated gestures when configured to run on end. Thanks to @d86leader

    https://github.com/JoseExposito/touchegg/issues/419

  - Using unaccelerated deltas and different horizontal and vertical finish thresholds for a better
    user experience

    https://github.com/JoseExposito/touchegg/issues/412

Fixed:

  - Fix crashes when incorrect keys are used on `SEND_KEYS`

    https://github.com/JoseExposito/touchegg/issues/392

    https://github.com/JoseExposito/touchegg/issues/419

  - Handle devices reporting a size of 0x0 mm

    https://github.com/JoseExposito/touchegg/issues/415

  - Allow to use a symlink as configuration to Dotfiles users

    https://github.com/JoseExposito/touchegg/issues/409

  - Handles window managers that don't set the `_NET_WORKAREA` atom

    https://github.com/JoseExposito/touchegg/issues/381

    https://github.com/JoseExposito/touchegg/issues/383


## 2.0.4 - 2020-12-07

New:

  - New gesture available for touchscreens: `TAP`

    https://github.com/JoseExposito/touchegg/issues/378

  - New action added: `MOUSE_CLICK`

    https://github.com/JoseExposito/touchegg/issues/378

Improvements:

  - Better multi-monitor support

    https://github.com/JoseExposito/touchegg/issues/364

    https://github.com/JoseExposito/touchegg/issues/396

  - Improve config file watcher

    https://github.com/JoseExposito/touchegg/issues/399


## 2.0.3 - 2020-11-17

New:

  - Use `auto` with `color` and `borderColor` to use your theme's accent color

    https://github.com/JoseExposito/touchegg/issues/360

  - Use `auto` with `CHANGE_DESKTOP` to follow your natural scroll preferences

    https://github.com/JoseExposito/touchegg/issues/382

Improvements:

  - You are downloading a much better Debian (.deb) package

    https://github.com/JoseExposito/touchegg/issues/384

  - Now Linux distributions shipping Touchégg by default can update your configuration easily

    https://github.com/JoseExposito/touchegg/issues/368

  - Improve protocol backward compatibility for third party integrations

    https://github.com/JoseExposito/touchegg/issues/385


## 2.0.2 - 2020-10-28

New:

  - Touchscreen support. Now you can use PINCH and SWIPE gestures on your touchscreen.

    https://github.com/JoseExposito/touchegg/issues/336

  - Animations are smoother, even in devices with limited resources like the Raspberry Pi 4.

    https://github.com/JoseExposito/touchegg/issues/372

  - CHANGE_DESKTOP now allows to use up/down/left/right directions in addition to previous/next.
    Made with love for KDE users.

    https://github.com/JoseExposito/touchegg/issues/338

  - Touchégg is added to startup automatically on installation.

    https://github.com/JoseExposito/touchegg/issues/361

  - In case you manually added it to startup you don't need to change anything, now you can not run
    multiple instances in parallel by mistake.

    https://github.com/JoseExposito/touchegg/issues/369

Fixed:

  - Crash when a screen is connected but disabled. Thanks to @magnus-gross.

    https://github.com/JoseExposito/touchegg/issues/341

  - Intermittent crash after editing the configuration file.

    https://github.com/JoseExposito/touchegg/issues/350

  - Crash when performing a gesture on the root window.

    https://github.com/JoseExposito/touchegg/issues/352


## 2.0.1 - 2020-09-29

This release is only a fix for Arch Linux and openSUSE compilation.

Fixed:

  - Fix Arch Linux and openSUSE compilation

    https://github.com/JoseExposito/touchegg/issues/337


## 2.0.0 - 2020-09-27

The Linux desktop has changed a lot since I first released Touchégg back in 2011.
This release is a total rewrite of the version 1.x aiming to incorporate the new technologies that
are available today on the Linux desktop.

Here's what's new:

  - Add libinput support
  - Add 1:1 animations so your gestures doesn't feel like a "shortcut" anymore
  - Drop the Qt dependency for better compatibility
  - Available gestures:
    - SWIPE
    - PINCH
  - Available actions:
    - MAXIMIZE_RESTORE_WINDOW
    - MINIMIZE_WINDOW
    - TILE_WINDOW
    - CLOSE_WINDOW
    - CHANGE_DESKTOP
    - SHOW_DESKTOP
    - SEND_KEYS
    - RUN_COMMAND


## 1.1.1 - 2015-06-08

  - Fix pinch direction issues
  - Allow to select if the action is executed at the beginning or at the end of the gesture


## 1.1.0 - 2012-07-22

  - Ubuntu Precise compatibility


## 1.0 - 2011-09-02

  - Now Touchégg subscribe to gestures in their own window, to not conflict with applications that uses their own gestures
  - Touchégg ported to GEIS v2 API
  - Touchégg now uses a XML configuration file more intuitive, easy and cleaned and some action configurations have been enhanced
  - The code is adapted to the Qt/KDE coding style
  - Added support for the following actions:
    - VERTICAL_SCROLL and HORIZONTALL_SCROLL actions now are SCROLL
    - The SCROLL action support invert the movement, for touchscreen/trackpad
      compatibility <https://code.google.com/p/touchegg/issues/detail?id=64>
  - Added support for the following gestures:
    - ROTATE     - With 2 to 5 fingers
    - DOUBLE_TAP - With 1 to 5 fingers
    - DRAG       - With 1 finger


## 0.3 - 2011-04-28

  - Touchégg now allow to assign different actions to different windows
  - Added compatibility with uTouch 2, and therefore, with the Synaptics driver
    and Ubuntu 11.04
  - Improved CPU usage
  - Touchégg allows to interact with all windows, not only active windows
    Now the actions are applied to the window under cursor
  - Solved problems when a trackpad is removed or added.

  - MOVE_WINDOW now don't moves the desktop window
  - RESIZE_WINDOW now don't resizes the desktop window
  - CLOSE_WINDOW now can be used with drag or tap&hold gestures
  - RESIZE WINDOW now is adapted to the angle of the pinch
  - MOVE_WINDOW allows to use Kwin/Compiz effects like "Wobbly Windows" or
    "Electric Borders"
  - The MOUSE_MOVE action has been removed because in Natty is deprecated

  - Added support for the following gestures:
    - PINCH - With 2, 4 and 5 fingers
    - DRAG - With 5 fingers

  - Added support for the following actions:
    - MOUSE_WHEEL_UP and MOUSE_WHEEL_DOWN actions now are VERTICAL_SCROLL
    - LEFT_BUTTON_CLICK, RIGHT_BUTTON_CLICK and MIDDLE_BUTTON_CLICK actions now are
      MOUSE_CLICK
    - HORIZONTAL_SCROLL
    - CHANGE_VIEWPORT
    - DRAG_AND_DROP now support any button emulation


## 0.2 - 2011-03-11

Solved bugs:
  - Solved problems at shutdown
  - Fixed _DESKTOP actions with compiz
  - Fixes some problems with the code

Added support for the following gestures:
  - TAP - With 5 fingers
  - TAP & HOLD - With 2, 3, 4 and 5 fingers

Added support for the following actions:
  - MOUSE_MOVE
  - LEFT_BUTTON_CLICK
  - MOVE_WINDOW
  - RUN_COMMAND
  - DRAG_AND_DROP
  - SEND_KEYS

Other features:
  - Added a GUI to manage gestures and actions
  - Added menu entries  to launch Touchégg and touchégg GUI


## 0.1 - 2011-01-23

Initial release, support for the following gestures:
  - TAP   - With 2, 3 and 4 fingers
  - PINCH - With 3 fingers
  - DRAG  - With 2, 3 and 4 fingers

Support for the following actions:
  - RIGHT_BUTTON_CLICK
  - MIDDLE_BUTTON_CLICK
  - MOUSE_WHEEL_UP
  - MOUSE_WHEEL_DOWN
  - MINIMIZE_WINDOW
  - MAXIMIZE_RESTORE_WINDOW
  - CLOSE_WINDOW
  - RESIZE_WINDOW
  - SHOW_DESKTOP
  - CHANGE_DESKTOP

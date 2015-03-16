# Introduction #

Then you can see a list with principal changes that have taken place between
diferent Touchégg versions.

# Changelog #

  * **Touchégg v0.1** (2011/01/23)
> Initial release, support for the following gestures:
    * TAP   - With 2, 3 and 4 fingers
    * PINCH - With 3 fingers
    * DRAG  - With 2, 3 and 4 fingers
> Support for the following actions:
    * RIGHT\_BUTTON\_CLICK
    * MIDDLE\_BUTTON\_CLICK
    * MOUSE\_WHEEL\_UP
    * MOUSE\_WHEEL\_DOWN
    * MINIMIZE\_WINDOW
    * MAXIMIZE\_RESTORE\_WINDOW
    * CLOSE\_WINDOW
    * RESIZE\_WINDOW
    * SHOW\_DESKTOP
    * CHANGE\_DESKTOP

  * **Touchégg v0.2** (2011/03/11)
> Solved bugs:
    * Solved problems at shutdown
    * Fixed _DESKTOP actions with compiz
    * Fixes some problems with the code
> Added support for the following gestures:
    * TAP - With 5 fingers
    * TAP & HOLD - With 2, 3, 4 and 5 fingers
> Added support for the following actions:
    * MOUSE\_MOVE
    * LEFT\_BUTTON\_CLICK
    * MOVE\_WINDOW
    * RUN\_COMMAND
    * DRAG\_AND\_DROP
    * SEND\_KEYS
> Other features:
    *_Added a GUI to manage gestures and actions_* Added menu entries  to launch Touchégg and touchégg GUI_

  * **Touchégg v0.3** (2011/04/28)
> New features:
    * Touchégg now allow to assign different actions to different windows
    * Added compatibility with uTouch 2, and therefore, with the Synaptics driver and Ubuntu 11.04
    * Improved CPU usage
    * Touchégg allows to interact with all windows, not only active windows. Now the actions are applied to the window under cursor
    * Solved problems when a trackpad is removed or added.
> Solved bugs and other improvements:
    * MOVE\_WINDOW now don't moves the desktop window
    * RESIZE\_WINDOW now don't resizes the desktop window
    * CLOSE\_WINDOW now can be used with drag or tap&hold gestures
    * RESIZE WINDOW now is adapted to the angle of the pinch
    * MOVE\_WINDOW allows to use Kwin/Compiz effects like "Wobbly Windows" or "Electric Borders"
    * The MOUSE\_MOVE action has been removed because in Natty is deprecated
> Added support for the following gestures:
    * PINCH - With 2, 4 and 5 fingers
    * DRAG - With 5 fingers
> Added support for the following actions:
    * MOUSE\_WHEEL\_UP and MOUSE\_WHEEL\_DOWN actions now are VERTICAL\_SCROLL
    * LEFT\_BUTTON\_CLICK, RIGHT\_BUTTON\_CLICK and MIDDLE\_BUTTON\_CLICK actions now are MOUSE\_CLICK
    * HORIZONTAL\_SCROLL
    * CHANGE\_VIEWPORT
    * DRAG\_AND\_DROP now support any button emulation

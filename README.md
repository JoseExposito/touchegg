**Follow Touchégg on...** [![Twitter](.github/images/twitter.png "Twitter")](https://twitter.com/Jose__Exposito)


# Touchégg:

Touchégg is an app that runs in the background and transform the gestures you make in your touchpad
into visible actions in your desktop.

For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to
switch to the next desktop.

Many more actions and gestures are available and everything is easily configurable.

<p align="center">
  <a href="https://www.youtube.com/watch?v=1Ek4QaFQ1qo">
    <img src="https://lh3.googleusercontent.com/jCG_VhjYFyY8HlyevwsSffoxYA065MI6NnWqB2sTDMdrm8M_WwuUbB9Gigyo8kKI6QSOPQbavegEHPpPsrNeDkBqbI3tviEqXAZrW6qlIO3ID2q1WcGbrhhJsi8vLUpOpH769weEzhsFdFbXXoIIbSHe3VIqwJ0LiIBnPFUeFAmwRQea4lv6soTWfU6ieyplP3eCAwxP6EZXhDUXhfgGPqVyfiR-capdju_BozL6mehoGAq1lm7W0JMIrw3wPxxifo7sibylEkCSx2m1zlpfnQ27qWtxM7ft97nBWamWTcZL8lB086_JXGznd91XVudasE9iNQS9zwLk7kg4WM8KNXl4mbV8RVqTANq9iBHorlZxPXAWy_xk_gbkDrMzUQirtZoN7J-4_bwqE3N68lzPdSsc5SMYH39YWR-qyCzPNMCvTv-ZXY8ygZeGBsbh7pQSZxu1DkFcYd7fZngpbU8n0VFk48uCReJve-sKXphQmr2hqkytJFew6YietBYDBYSVBAv1LBPwzLjt0iPuCVOVT04lK-uNemhmZV-5FVaQYO9rxFMufq58pz8ygaVyQ8If-sl7=w854-h480-no" alt="YouTube" />
  </a>
</p>

For more information check the [wiki](https://github.com/JoseExposito/touchegg/wiki) or
[ask a question](https://github.com/JoseExposito/touchegg/issues).


# Available actions:

## Maximize or restore a window (MAXIMIZE_RESTORE_WINDOW)

Maximize the window under the pointer. If it is already maximized, restore it.

Options:

| Option | Values | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="SWIPE" fingers="3" direction="UP">
  <action type="MAXIMIZE_RESTORE_WINDOW">
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/MAXIMIZE_RESTORE_WINDOW.gif)

## Minimize a window (MINIMIZE_WINDOW)

Minimize the window under the pointer.

Options:

| Option | Values | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="SWIPE" fingers="3" direction="DOWN">
  <action type="MINIMIZE_WINDOW">
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/MINIMIZE_WINDOW.gif)

## Tile/snap a widow (TILE_WINDOW)

Resize and move the window under the pointer to use half of the screen.

Options:

| Option | Values | Description |
| - | - | - |
| direction | `left`/`right` | Use the `left` or `right` half of the screen |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="SWIPE" fingers="3" direction="LEFT">
  <action type="TILE_WINDOW">
    <direction>right</direction>
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>

<gesture type="SWIPE" fingers="3" direction="RIGHT">
  <action type="TILE_WINDOW">
    <direction>left</direction>
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/TILE_WINDOW.gif)

## Switch desktops/workspaces (CHANGE_DESKTOP)

Change to the next or previous desktop/workspace.

Options:

| Option | Values | Description |
| - | - | - |
| direction | `left`/`right` | Use the `left` or `right` half of the screen |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="SWIPE" fingers="4" direction="LEFT">
  <action type="CHANGE_DESKTOP">
    <direction>next</direction>
    <animate>true</animate>
    <animationPosition>right</animationPosition>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>

<gesture type="SWIPE" fingers="4" direction="RIGHT">
  <action type="CHANGE_DESKTOP">
    <direction>previous</direction>
    <animate>true</animate>
    <animationPosition>left</animationPosition>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/CHANGE_DESKTOP.gif)

## Keyboard shortcut (SEND_KEYS)

Emulate a keyboard shortcut.

Options:

| Option | Values | Description |
| - | - | - |
| repeat | `true`/`false` | `true` if the keyboard shortcut should be executed multiple times. `false` otherwise. This is useful to perform actions like pinch to zoom. |
| modifiers | Keycode | Typical values are: Shift_L, Control_L, Alt_L, Alt_R, Meta_L, Super_L, Hyper_L. You can use multiple keycodes: `Control_L+Alt_L`.See "Keycodes" bellow for more information. |
| keys | Keycode | Shortcut keys. You can use multiple keycodes: `A+B+C`. See "Keycodes" bellow for more information. |
| on | `begin`/`end` | Only used when `repeat` is `true`. If the shortcut should be executed on the beginning or on the end of the gesture. |
| decreaseKeys | Keycode | Only used when `repeat` is `false`. Keys to press when you change the gesture direction to the opposite. You can use multiple keycodes: `A+B+C`. This is useful to perform actions like pinch to zoom, check `Example 2` bellow. |

Keycodes:

For a full list of key codes, open `/usr/include/X11/keysymdef.h` with your favorite text editor.

It is important to remove the `XK_` prefix. For example, the super keycode is defined as
`XK_Super_L` but it must be used as `Super_L` in the configuration.

Example 1:

```
<gesture type="SWIPE" fingers="4" direction="UP">
  <action type="SEND_KEYS">
    <repeat>false</repeat>
    <modifiers>Super_L</modifiers>
    <keys>W</keys>
    <on>begin</on>
  </action>
</gesture>
```

Example 2: Pinch to zoom example

```
<gesture type="PINCH" fingers="2" direction="OUT">
  <action type="SEND_KEYS">
    <repeat>true</repeat>
    <modifiers>Control_L</modifiers>
    <keys>KP_Add</keys>
    <decreaseKeys>KP_Subtract</decreaseKeys>
  </action>
</gesture>
```

# Execute a command (RUN_COMMAND)

Run any command.

Options:

| Option | Values | Description |
| - | - | - |
| repeat | `true`/`false` | `true` if the command should be executed multiple times. `false` otherwise. |
| command | Command | The command to execute. |
| on | `begin`/`end` | Only used when `repeat` is `true`. If the command should be executed on the beginning or on the end of the gesture. |
| decreaseCommand | Keycode | Only used when `repeat` is `false`. Command to run when you change the gesture direction to the opposite. Check `Example 2` bellow. |

Example 1:

```
<gesture type="SWIPE" fingers="4" direction="DOWN">
  <action type="RUN_COMMAND">
    <repeat>false</repeat>
    <command>notify-send 'Hello' 'World'</command>
    <on>begin</on>
  </action>
</gesture>
```

Example 2:

```
<gesture type="SWIPE" fingers="4" direction="DOWN">
  <action type="RUN_COMMAND">
    <repeat>true</repeat>
    <command>notify-send 'Swipe direction' 'DOWN'</command>
    <decreaseCommand>notify-send 'Swipe direction' 'UP'</decreaseCommand>
  </action>
</gesture>
```


# Compilation and installation:

Follow the instructions available in the [HACKING.md](HACKING.md) file.


# Copyright:

Copyright 2011 - 2020 José Expósito <<jose.exposito89@gmail.com>>

The source code is available under GPL v2 license on [GitHub](https://github.com/JoseExposito/touchegg)

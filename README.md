**Follow Touchégg on...** [![Twitter](.github/images/twitter.png "Twitter")](https://twitter.com/Jose__Exposito)


# Touchégg

Touchégg is an app that runs in the background and transform the gestures you make on your touchpad
into visible actions in your desktop.

For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to
switch to the next desktop.

Many more actions and gestures are available and everything is easily configurable.

<p align="center">
  <a href="https://www.youtube.com/watch?v=1Ek4QaFQ1qo">
    <img src="https://lh3.googleusercontent.com/jCG_VhjYFyY8HlyevwsSffoxYA065MI6NnWqB2sTDMdrm8M_WwuUbB9Gigyo8kKI6QSOPQbavegEHPpPsrNeDkBqbI3tviEqXAZrW6qlIO3ID2q1WcGbrhhJsi8vLUpOpH769weEzhsFdFbXXoIIbSHe3VIqwJ0LiIBnPFUeFAmwRQea4lv6soTWfU6ieyplP3eCAwxP6EZXhDUXhfgGPqVyfiR-capdju_BozL6mehoGAq1lm7W0JMIrw3wPxxifo7sibylEkCSx2m1zlpfnQ27qWtxM7ft97nBWamWTcZL8lB086_JXGznd91XVudasE9iNQS9zwLk7kg4WM8KNXl4mbV8RVqTANq9iBHorlZxPXAWy_xk_gbkDrMzUQirtZoN7J-4_bwqE3N68lzPdSsc5SMYH39YWR-qyCzPNMCvTv-ZXY8ygZeGBsbh7pQSZxu1DkFcYd7fZngpbU8n0VFk48uCReJve-sKXphQmr2hqkytJFew6YietBYDBYSVBAv1LBPwzLjt0iPuCVOVT04lK-uNemhmZV-5FVaQYO9rxFMufq58pz8ygaVyQ8If-sl7=w854-h480-no" alt="YouTube" />
  </a>
</p>


# Table of contents

  * [Installation](#installation)
  * [Configuration](#configuration)
    * [Global settings](#global-settings)
    * [Available gestures](#available-gestures)
      * [Swipe](#swipe)
      * [Pinch](#pinch)
    * [Available actions](#available-actions)
      * [Maximize or restore a window](#maximize-or-restore-a-window-maximize_restore_window)
      * [Minimize a window](#minimize-a-window-minimize_window)
      * [Tile/snap a widow](#tilesnap-a-widow-tile_window)
      * [Close a window](#close-a-window-close_window)
      * [Switch desktops/workspaces](#switch-desktopsworkspaces-change_desktop)
      * [Show desktop](#show-desktop-show_desktop)
      * [Keyboard shortcut](#keyboard-shortcut-send_keys)
      * [Execute a command](#execute-a-command-run_command)
    * [Daemon configuration](#daemon-configuration)
  * [Copyright](#copyright)


# Installation

On the [releases](https://github.com/JoseExposito/touchegg/releases) page you will find a package
for your distribution.

Otherwise you can compile the source code yourself by following the instructions available in the
[HACKING.md](HACKING.md) file.

## Ubuntu, Debian and derivatives

Download the `.deb` package and install it. Double click on the package may work, otherwise install
it from the terminal:

```
$ cd ~/Downloads # Or to the path where the deb package is placed at
$ sudo dpkg -i touchegg_*.deb # Install the package
$ sudo apt -f install # Install missing dependencies
$ touchegg # Run Touchégg
```

## Red Hat, Fedora, CentOS and derivatives

Download the `.rpm` package and install it. Double click on the package may work, otherwise install
it from the terminal:

```
$ cd ~/Downloads # Or to the path where the rpm package is placed at
$ sudo yum localinstall touchegg-*.rpm # Install the package
```

## Add Touchégg to Startup Applications

Depending on your desktop environment, this step is different
You can easily add Touchégg to your startup applications following this steps:

  * [Gnome](https://help.ubuntu.com/stable/ubuntu-help/startup-applications.html.en): Add
    `/usr/bin/touchegg` as command
  * [KDE](https://docs.kde.org/trunk5/en/kde-workspace/kcontrol/autostart/index.html): Add
    `/usr/bin/touchegg` as script symlink
  * elementary OS: Open [System Settings](https://elementary.io/docs/learning-the-basics#system-settings)
    -> Applications -> Startup -> Add custom command -> `/usr/bin/touchegg`


# Configuration

After [installing](#installation) Touchégg you'll notice that you can start using multi-touch
gestures. However, you are not forced to use the gestures and actions that come out of the box, you
can configure the gestures you'd like to use and the actions they'll trigger.

Your configuration file is placed in `~/.config/touchegg/touchegg.conf`, open it with your favorite
text editor. It is a XML document with 3 main sections:

  * [Global settings](#global-settings)
  * Global gestures: `<application name="All">...</application>`
  * Application specified gestures: `<application name="Google-chrome,Firefox"></application>`

Find more information in the sections below.


## Global settings

| Option | Value | Default | Description | Example
| - | - | - | - | - |
| animation_delay | Number | 150 | Delay, in milliseconds, since the gesture starts before the animation is displayed | Use the MAXIMIZE_RESTORE_WINDOW action. You will notice that no animation is displayed if you complete the action quick enough. This property configures that time |
| action_execute_threshold | Number | 20 | Percentage of the animation to be completed to apply the action | Use the MAXIMIZE_RESTORE_WINDOW action. You will notice that, even if the animation is displayed, the action is not executed if you did not moved your fingers far enough. This property configures the percentage of the animation that must be reached to execute the action |
| color | Hex color | 3E9FED | Color of the animation | `#909090`
| borderColor | Hex color | 3E9FED | Color of the animation | `FFFFFF`


## Available gestures

### Swipe

From [libinput documentation](https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#swipe-gestures):
Swipe gestures are executed when three or more fingers are moved synchronously in the same
direction.

Example:

```
<gesture type="SWIPE" fingers="3" direction="UP">
  <action type="MAXIMIZE_RESTORE_WINDOW">
    <animate>true</animate>
  </action>
</gesture>
```

### Pinch

From [libinput documentation](https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#pinch-gestures):
Pinch gestures are executed when two or more fingers are located on the touchpad and are either
changing the relative distance to each other (pinching) or are changing the relative angle (rotate).

Example:

```
<gesture type="PINCH" fingers="4" direction="IN">
  <action type="CLOSE_WINDOW">
    <animate>true</animate>
    <color>F84A53</color>
    <borderColor>F84A53</borderColor>
  </action>
</gesture>
```


## Available actions

### Maximize or restore a window (MAXIMIZE_RESTORE_WINDOW)

Maximize the window under the pointer. If it is already maximized, restore it.

Options:

| Option | Value | Description |
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

### Minimize a window (MINIMIZE_WINDOW)

Minimize the window under the pointer.

Options:

| Option | Value | Description |
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

### Tile/snap a widow (TILE_WINDOW)

Resize and move the window under the pointer to use half of the screen.

Options:

| Option | Value | Description |
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

### Close a window (CLOSE_WINDOW)

Close the window under the pointer.

Options:

| Option | Value | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="PINCH" fingers="4" direction="IN">
  <action type="CLOSE_WINDOW">
    <animate>true</animate>
    <color>F84A53</color>
    <borderColor>F84A53</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/CLOSE_WINDOW.gif)

### Switch desktops/workspaces (CHANGE_DESKTOP)

Change to the next or previous desktop/workspace.

Options:

| Option | Value | Description |
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

### Show desktop (SHOW_DESKTOP)

Show the desktop. If the desktop is already being shown, restore all the windows.

Options:

| Option | Value | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="SWIPE" fingers="4" direction="DOWN">
  <action type="SHOW_DESKTOP">
    <animate>true</animate>
    <color>909090</color>
    <borderColor>FFFFFF</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/SHOW_DESKTOP.gif)

### Keyboard shortcut (SEND_KEYS)

Emulate a keyboard shortcut.

Options:

| Option | Value | Description |
| - | - | - |
| repeat | `true`/`false` | `true` if the keyboard shortcut should be executed multiple times. `false` otherwise. This is useful to perform actions like pinch to zoom. |
| modifiers | Keycode | Typical values are: Shift_L, Control_L, Alt_L, Alt_R, Meta_L, Super_L, Hyper_L. You can use multiple keycodes: `Control_L+Alt_L`.See "Keycodes" below for more information. |
| keys | Keycode | Shortcut keys. You can use multiple keycodes: `A+B+C`. See "Keycodes" below for more information. |
| on | `begin`/`end` | Only used when `repeat` is `true`. If the shortcut should be executed on the beginning or on the end of the gesture. |
| decreaseKeys | Keycode | Only used when `repeat` is `false`. Keys to press when you change the gesture direction to the opposite. You can use multiple keycodes: `A+B+C`. This is useful to perform actions like pinch to zoom, check `Example 2` below. |

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
<gesture type="PINCH" fingers="2" direction="IN">
  <action type="SEND_KEYS">
    <repeat>true</repeat>
    <modifiers>Control_L</modifiers>
    <keys>KP_Subtract</keys>
    <decreaseKeys>KP_Add</decreaseKeys>
  </action>
</gesture>

<gesture type="PINCH" fingers="2" direction="OUT">
  <action type="SEND_KEYS">
    <repeat>true</repeat>
    <modifiers>Control_L</modifiers>
    <keys>KP_Add</keys>
    <decreaseKeys>KP_Subtract</decreaseKeys>
  </action>
    </gesture>
```

### Execute a command (RUN_COMMAND)

Run any command.

Options:

| Option | Value | Description |
| - | - | - |
| repeat | `true`/`false` | `true` if the command should be executed multiple times. `false` otherwise. |
| command | Command | The command to execute. |
| on | `begin`/`end` | Only used when `repeat` is `true`. If the command should be executed on the beginning or on the end of the gesture. |
| decreaseCommand | Keycode | Only used when `repeat` is `false`. Command to run when you change the gesture direction to the opposite. Check `Example 2` below. |

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


## Daemon configuration

This is an advanced topic and my recommendation is to ignore it.

Touchégg runs in two different processes, one of them is a systemd daemon configured in
`/lib/systemd/system/touchegg.service`. In addition to the `--daemon` argument, you can pass two optional arguments:

| Option | Value | Default | Description | Example
| - | - | - | - | - |
| threshold | Number | Calculated automatically according to your device characteristics | Amount of motion to be made on the touchpad before a gesture is started | Put 3 fingers on your touchpad. You will notice that the action does not start until you move them a little bit. This property configures how much you should move your fingers before the action starts |
| animation_finish_threshold | Number | Calculated automatically according to your device characteristics | Amount of motion to be made on the touchpad to reach the 100% of an animation | Use the MAXIMIZE_RESTORE_WINDOW action. You will notice that you need to move your fingers a certain ammount until the animation fills your entire screen. This property configures how much you need to move your fingers |

It is recommended NOT to configure `threshold` and `animation_finish_threshold` since an optimal
value is calculated for you. This value is printed to the terminal on application startup or when a
new multi-touch device is connected.

Example:

```
$ cat /lib/systemd/system/touchegg.service | grep ExecStart
ExecStart=/usr/bin/touchegg --daemon 100 500

$ sudo systemctl daemon-reload && sudo systemctl restart touchegg

$ journalctl -u touchegg -b -f
Compatible device detected:
  Name: Apple Inc. Magic Trackpad 2
  Size: 161.957mm x 115.114mm
  Calculating threshold and animation_finish_threshold. You can tune this values in your service file
  threshold: 100
  animation_finish_threshold: 500
```


# Copyright

Copyright 2011 - 2020 José Expósito <<jose.exposito89@gmail.com>>

The source code is available under GPL v2 license on [GitHub](https://github.com/JoseExposito/touchegg)

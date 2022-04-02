**Follow Touchégg on...** [![Twitter](.github/images/twitter.png "Twitter")](https://twitter.com/Jose__Exposito) <a href="https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=FT2KS37PVG8PU&currency_code=EUR&source=url"><img align="right"  src="https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif"></a>


# Touchégg

Touchégg is an app that runs in the background and transform the gestures you make on your touchpad
or touchscreen into visible actions in your desktop.

For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to
switch to the next desktop.

Many more actions and gestures are available and everything is easily configurable.

![Demo](.github/images/Ubuntu.gif)

<p align="center">
  <a href="https://youtu.be/PLsH-XPFuN4">:movie_camera: Ubuntu demo</a>
  <br/>
  <a href="https://youtu.be/nuMT-MwyTXU">:movie_camera: elementary OS demo</a>
  <br/>
  <a href="https://www.youtube.com/watch?v=7gKONPKNZlc">:movie_camera: Touchscreen demo</a>
</p>

# Table of contents

  * [Installation](#installation)
    * [Ubuntu, Debian and derivatives](#ubuntu-debian-and-derivatives)
    * [Fedora, CentOS, RHEL and derivatives](#fedora-centos-rhel-and-derivatives)
    * [Arch Linux, Manjaro and derivatives](#arch-linux-manjaro-and-derivatives)
    * [openSUSE](#opensuse)
    * [Alpine Linux](#alpine-linux)
    * [Void Linux](#void-linux)
    * [GNOME](#gnome)
  * [Configuration](#configuration)
    * [Using Touché](#using-touché)
    * [Manual configuration](#manual-configuration)
    * [Global settings](#global-settings)
    * [Available gestures](#available-gestures)
      * [Swipe](#swipe)
      * [Pinch](#pinch)
      * [Tap](#tap)
    * [Available actions](#available-actions)
      * [Maximize or restore a window](#maximize-or-restore-a-window-maximize_restore_window)
      * [Minimize a window](#minimize-a-window-minimize_window)
      * [Tile/snap a window](#tilesnap-a-window-tile_window)
      * [Fullscreen a window](#fullscreen-a-window-fullscreen_window)
      * [Close a window](#close-a-window-close_window)
      * [Switch desktops/workspaces](#switch-desktopsworkspaces-change_desktop)
      * [Show desktop](#show-desktop-show_desktop)
      * [Keyboard shortcut](#keyboard-shortcut-send_keys)
      * [Execute a command](#execute-a-command-run_command)
      * [Mouse click](#mouse-click-mouse_click)
    * [Custom animations](#custom-animations)
    * [Daemon configuration](#daemon-configuration)
  * [FAQ](#faq)
  * [Copyright](#copyright)


# Installation

On the [releases](https://github.com/JoseExposito/touchegg/releases) page you will find a package
for your distribution.

Otherwise you can compile the source code yourself by following the instructions available in the
[HACKING.md](HACKING.md) file.

## Ubuntu, Debian and derivatives

On Ubuntu, it is recommended to use the
[official PPA](https://launchpad.net/~touchegg/+archive/ubuntu/stable) to install Touchégg and
receive updates:

```bash
$ sudo add-apt-repository ppa:touchegg/stable
$ sudo apt update
$ sudo apt install touchegg
```

If PPAs are not available on your operating system,
[download](https://github.com/JoseExposito/touchegg/releases) the `.deb` package and install it.
Double click on the package may work, otherwise install it from the terminal:

```bash
$ cd ~/Downloads # Or to the path where the deb package is placed at
$ sudo apt install ./touchegg_*.deb # Install the package
```

Run Touchégg manually by running the command `touchegg` or reboot to get started.

Included by default on elementary OS 6, Zorin OS 16 and Pop!\_OS 21.04+

## Fedora, CentOS, RHEL and derivatives

On Fedora and CentOS (EPEL) it is recommended to use the
[official COPR](https://copr.fedorainfracloud.org/coprs/joseexposito/touchegg/) to install Touchégg and
receive updates.

```bash
$ sudo dnf copr enable joseexposito/touchegg
$ sudo dnf install touchegg
```

On other RPM based operating systems,
[download](https://github.com/JoseExposito/touchegg/releases) the `.rpm` package and install it.
Double click on the package may work, otherwise install it from the terminal:

```bash
$ cd ~/Downloads # Or to the path where the rpm package is placed at
$ sudo dnf install touchegg-*.rpm # Install the package
```

Run Touchégg manually by running the command `touchegg` or reboot to get started.

## Arch Linux, Manjaro and derivatives

Install the `touchegg` package from [AUR](https://aur.archlinux.org/packages/touchegg/).

Notice that on Arch services are not enabled or started by default, so you'll have to do it manually:

```bash
$ sudo systemctl enable touchegg.service
$ sudo systemctl start touchegg
```

Once the service is enabled, run Touchégg manually by running the command `touchegg` or reboot to get started.

A version for Arch based distributions without systemd support, like Artix, is also available on [AUR](https://aur.archlinux.org/packages/touchegg-nosystemd/)

## openSUSE

Touchégg is available in the [official repositories](https://software.opensuse.org/package/touchegg).

```bash
$ sudo zypper install touchegg
$ sudo systemctl enable touchegg.service
$ sudo systemctl start touchegg
```

If the version of Touchégg included for your distro is too old (v1.x)
it is recommended to use the
[official COPR](https://copr.fedorainfracloud.org/coprs/joseexposito/touchegg/) to install Touchégg and
receive updates.

## Alpine Linux

Uncomment the url for the testing repository in /etc/apk/repositories, then install:

```bash
$ sudo apk update
$ sudo apk add touchegg
```

The Touchégg package includes an Openrc init script for starting the Touchégg daemon at boot. To enable:

```bash
$ sudo rc-update add touchegg
```
The init script can also be used to manually start and stop the Touchégg daemon as required:

```bash
$ sudo rc-service touchegg start
$ sudo rc-service touchegg stop
```

## Void Linux

Touchégg is available from the main repository. To use it, you have to enable its service after installing.

```bash
$ sudo xbps-install touchegg
$ sudo ln -s /etc/sv/touchegg /var/service
```

## GNOME

If you are using the GNOME Desktop Environment it is recommended to also install this extension:

https://github.com/JoseExposito/gnome-shell-extension-x11gestures

Both Touchégg and the extension need to installed, so don't forget to follow the install
instructions for your distro!


# Configuration

After [installing](#installation) Touchégg you'll notice that you can start using multi-touch
gestures. However, you are not forced to use the gestures and actions that come out of the box, you
can configure the gestures you'd like to use and the actions they'll trigger.

## Using Touché

[Touché](https://github.com/JoseExposito/touche) is a desktop application to easily configure your
touchpad and touchscreen multi-touch gestures.

<div align="center">

  ![Touché on GNOME](https://raw.githubusercontent.com/JoseExposito/touche/master/.github/images/adwaita.png)

</div>

Follow the instructions on [the project page](https://github.com/JoseExposito/touche) to install it.

## Manual configuration

[Touché](https://github.com/JoseExposito/touche) is the recommended way of configuring your
gestures. However, you can also manually configure Touchégg by editing an XML file.

Start by copying the default configuration from `/usr/share/touchegg/touchegg.conf` to
`~/.config/touchegg/touchegg.conf`. You can do it using your file manager or by running this command
in your terminal:

```bash
$ mkdir -p ~/.config/touchegg && cp -n /usr/share/touchegg/touchegg.conf ~/.config/touchegg/touchegg.conf
```

Now open `~/.config/touchegg/touchegg.conf` with your favorite text editor.
It is a XML document with 3 main sections:

  * [Global settings](#global-settings)
  * Global gestures: `<application name="All">...</application>`
  * Application specific gestures: `<application name="Google-chrome,Firefox"></application>`

    The application name can be obtained by running this command and clicking on the target application window:
    ```bash
    $ xprop | grep WM_CLASS
    ```

Find more information in the sections below.


## Global settings

| Option | Value | Default | Description | Example
| - | - | - | - | - |
| animation_delay | Number | 150 | Delay, in milliseconds, since the gesture starts before the animation is displayed | Use the MAXIMIZE_RESTORE_WINDOW action. You will notice that no animation is displayed if you complete the action quick enough. This property configures that time |
| action_execute_threshold | Number | 20 | Percentage of the gesture to be completed to apply the action. Set to 0 to execute actions unconditionally | Use the MAXIMIZE_RESTORE_WINDOW action. You will notice that, even if the animation is displayed, the action is not executed if you did not move your fingers far enough. This property configures the percentage of the gesture that must be reached to execute the action |
| color | Hex color | 3E9FED | Color of the animation | `#909090`
| borderColor | Hex color | 3E9FED | Color of the animation | `FFFFFF`


## Available gestures

### Swipe

From [libinput documentation](https://wayland.freedesktop.org/libinput/doc/latest/gestures.html#swipe-gestures):
Swipe gestures are executed when three or more fingers are moved synchronously in the same
direction.

Note that **three** is the minimum number of fingers that Touchégg allows for swipe gestures on
touchpads and **two** on touchscreens.

Example:

```xml
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

```xml
<gesture type="PINCH" fingers="4" direction="IN">
  <action type="CLOSE_WINDOW">
    <animate>true</animate>
    <color>F84A53</color>
    <borderColor>F84A53</borderColor>
  </action>
</gesture>
```

### Tap

Tap gestures are executed when two or more fingers "click" on the touchscreen.

**Only available on touchscreens**

Example:

```xml
<gesture type="TAP" fingers="2">
  <action type="MOUSE_CLICK">
    <button>3</button>
    <on>begin</on>
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

```xml
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

```xml
<gesture type="SWIPE" fingers="3" direction="DOWN">
  <action type="MINIMIZE_WINDOW">
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/MINIMIZE_WINDOW.gif)

### Tile/snap a window (TILE_WINDOW)

Resize and move the window under the pointer to use half of the screen.

Options:

| Option | Value | Description |
| - | - | - |
| direction | `left`/`right` | Use the `left` or `right` half of the screen |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```xml
<gesture type="SWIPE" fingers="3" direction="LEFT">
  <action type="TILE_WINDOW">
    <direction>left</direction>
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>

<gesture type="SWIPE" fingers="3" direction="RIGHT">
  <action type="TILE_WINDOW">
    <direction>right</direction>
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/TILE_WINDOW.gif)

### Fullscreen a window (FULLSCREEN_WINDOW)

Toggles fullscreen mode for the window under the pointer.

Options:

| Option | Value | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```xml
<gesture type="SWIPE" fingers="3" direction="UP">
  <action type="FULLSCREEN_WINDOW">
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

### Close a window (CLOSE_WINDOW)

Close the window under the pointer.

Options:

| Option | Value | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```xml
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

Change to another desktop/workspace.

Options:

| Option | Value | Description |
| - | - | - |
| direction | `previous`/`next`/`up`/`down`/`left`/`right`/`auto` | The desktop/workspace to switch to. It is recommended to use `previous`/`next` for better compatibility. However, some desktop environments, like KDE, allow to configure a grid of desktops and `up`/`down`/`left`/`right` come in handy. With `SWIPE` gestures, `auto` will use your natural scroll preferences to figure out the direction. |
| cyclic | `true`/`false` | Set it to `true` when using `previous`/`next` directions to navigate from last desktop to first desktop or from first to last. |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| animationPosition | `up`/`down`/`left`/`right`/`auto` | Edge of the screen where the animation will be displayed. With `SWIPE` gestures, `auto` will use your natural scroll preferences to figure out the animation position. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```xml
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

```xml
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
| repeat | `true`/`false` | Whether to execute the keyboard shortcut multiple times (default: `false`). This is useful to perform actions like pinch to zoom. |
| modifiers | Keysym | Typical values are: `Shift_L`, `Control_L`, `Alt_L`, `Alt_R`, `Meta_L`, `Super_L`, `Hyper_L`. You can use multiple keysyms: `Control_L+Alt_L`.See "Keysyms" below for more information. |
| keys | Keysym | Shortcut keys. You can use multiple keysyms: `A+B+C`. See "Keysyms" below for more information. |
| on | `begin`/`end` | Only used when `repeat` is `false`. Whether to execute the shortcut at the beginning or at the end of the gesture. |
| decreaseKeys | Keysym | Only used when `repeat` is `true`. Keys to press when you change the gesture direction to the opposite. You can use multiple keysyms: `A+B+C`. This is useful to perform actions like pinch to zoom, check `Example 2` below. |
| times | 2...15 | Only used when `repeat` is `true`. Number of times to repeat the action. |
| animate | `true`/`false` | Set it to `true` to display the animation set in `animation`. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |
| animation | Animation | See [custom animations](#custom-animations) |

Keysyms:

Keysyms can be found in two places:
 - Regular keys are in `/usr/include/X11/keysymdef.h`, you can open it with your favorite text editor.

   It is important to remove the `XK_` prefix. For example, the super keysym is defined as
   `XK_Super_L` but it must be used as `Super_L` in the configuration.
 - Special keys (e.g. media keys, browser back, sleep, etc.) are in `/usr/include/X11/XF86keysym.h`.

   Again, remove `XK_`, but leave the rest (including the bit before the
   `XK_`). For example, `XF86XK_Back` becomes `XF86Back`.

Note that only keysyms that are mapped onto a keycode can be used by
Touchégg. You can use `xmodmap -pk` to show the current mapping. To add
a keysym that is not mapped by default (for example `XF86ZoomIn`), you
can tell `xmodmap` to map it to any free keycode:

    xmodmap -e 'keycode any=XF86ZoomIn'

Example 1: Pinch to zoom example

```xml
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

Example 2: Switch between windows (Alt+Tab)

```xml
<gesture type="SWIPE" fingers="3" direction="LEFT">
  <action type="SEND_KEYS">
    <repeat>true</repeat>
    <modifiers>Alt_L</modifiers>
    <keys>Shift_L+Tab</keys>
    <decreaseKeys>Tab</decreaseKeys>
  </action>
</gesture>

<gesture type="SWIPE" fingers="3" direction="RIGHT">
  <action type="SEND_KEYS">
    <repeat>true</repeat>
    <modifiers>Alt_L</modifiers>
    <keys>Tab</keys>
    <decreaseKeys>Shift_L+Tab</decreaseKeys>
  </action>
</gesture>
```

Example 3: Open Gnome application launcher

```xml
<gesture type="PINCH" fingers="4" direction="IN">
  <action type="SEND_KEYS">
    <repeat>false</repeat>
    <modifiers>Super_L</modifiers>
    <keys>A</keys>
    <on>begin</on>
  </action>
</gesture>
```

![Animation](.github/images/SEND_KEYS.gif)

### Execute a command (RUN_COMMAND)

Run any command.

Options:

| Option | Value | Description |
| - | - | - |
| repeat | `true`/`false` | `true` if the command should be executed multiple times. `false` otherwise. |
| command | Command | The command to execute. |
| on | `begin`/`end` | Only used when `repeat` is `false`. If the command should be executed on the beginning or on the end of the gesture. |
| decreaseCommand | Command | Only used when `repeat` is `true`. Command to run when you change the gesture direction to the opposite. Check `Example 2` below. |
| times | 2...15 | Only used when `repeat` is `true`. Number of times to repeat the action. |
| animate | `true`/`false` | Set it to `true` to display the animation set in `animation`. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |
| animation | Animation | See [custom animations](#custom-animations) |

Example 1:

```xml
<gesture type="SWIPE" fingers="4" direction="DOWN">
  <action type="RUN_COMMAND">
    <repeat>false</repeat>
    <command>notify-send 'Hello' 'World'</command>
    <on>begin</on>
  </action>
</gesture>
```

Example 2:

```xml
<gesture type="SWIPE" fingers="4" direction="DOWN">
  <action type="RUN_COMMAND">
    <repeat>true</repeat>
    <command>notify-send 'Swipe direction' 'DOWN'</command>
    <decreaseCommand>notify-send 'Swipe direction' 'UP'</decreaseCommand>
  </action>
</gesture>
```

### Mouse click (MOUSE_CLICK)

Emulate a mouse click.

Options:

| Option | Value | Description |
| - | - | - |
| button | `1`/`2`/`3` | Left click (1), middle click (2) or right click (3) |
| on | `begin`/`end` | If the command should be executed on the beginning or on the end of the gesture. |

Example:

```xml
<gesture type="TAP" fingers="2">
  <action type="MOUSE_CLICK">
    <button>3</button>
    <on>begin</on>
  </action>
</gesture>
```


## Custom animations

The [keyboard shortcut action](#keyboard-shortcut-send_keys) and the [execute a command action](#execute-a-command-run_command)
allow to set a custom animation. These are the available values:

| Animation | Example |
| - | - |
| CHANGE_DESKTOP_UP | [Switch desktops/workspaces](#switch-desktopsworkspaces-change_desktop) |
| CHANGE_DESKTOP_DOWN | [Switch desktops/workspaces](#switch-desktopsworkspaces-change_desktop) |
| CHANGE_DESKTOP_LEFT | [Switch desktops/workspaces](#switch-desktopsworkspaces-change_desktop) |
| CHANGE_DESKTOP_RIGHT | [Switch desktops/workspaces](#switch-desktopsworkspaces-change_desktop) |
| CLOSE_WINDOW | [Close a window](#close-a-window-close_window) |
| MAXIMIZE_WINDOW | [Maximize or restore a window](#maximize-or-restore-a-window-maximize_restore_window) |
| RESTORE_WINDOW | [Maximize or restore a window](#maximize-or-restore-a-window-maximize_restore_window) |
| MINIMIZE_WINDOW | [Minimize a window](#minimize-a-window-minimize_window) |
| SHOW_DESKTOP | [Show desktop](#show-desktop-show_desktop) |
| EXIST_SHOW_DESKTOP | [Show desktop](#show-desktop-show_desktop) |
| TILE_WINDOW_LEFT | [Tile/snap a window](#tilesnap-a-window-tile_window) |
| TILE_WINDOW_RIGHT | [Tile/snap a window](#tilesnap-a-window-tile_window) |


## Daemon configuration

Touchégg runs in two different processes, one of them is a systemd daemon configured in
`/lib/systemd/system/touchegg.service`. In addition to the `--daemon` argument, you can pass two optional arguments:

| Option | Value | Default | Description | Example
| - | - | - | - | - |
| start_threshold | Number | Calculated automatically according to your device characteristics | Amount of motion to be made on the touchpad before a gesture is started | Put 3 fingers on your touchpad. You will notice that the action does not start until you move them a little bit. This property configures how much you should move your fingers before the action starts |
| finish_threshold | Number | Calculated automatically according to your device characteristics | Amount of motion to be made on the touchpad to reach the 100% of an animation | Use the MAXIMIZE_RESTORE_WINDOW action. You will notice that you need to move your fingers a certain amount until the animation fills your entire screen. This property configures how much you need to move your fingers |

It is recommended NOT to configure `start_threshold` and `finish_threshold` since an optimal value
is calculated for you.

However, if your device size is unknown, you will need to set their values manually:

```
$ journalctl -u touchegg -b
[...]
It wasn't possible to get your device physical size, falling back to default start_threshold and finish_threshold. You can tune this values in your service file:
https://github.com/JoseExposito/touchegg#daemon-configuration
```

The recommended values are:

- start_threshold: The 3% of the height of your screen in mm
- finish_threshold: The 15% of the height of your screen in mm

For example, if your screen height is 100mm, edit `/lib/systemd/system/touchegg.service`
and set the right values:

```bash
ExecStart=/usr/bin/touchegg --daemon 3 15
```

Finally, restart the daemon and make sure the right values are printed:

```bash
$ sudo systemctl daemon-reload && sudo systemctl restart touchegg

$ journalctl -u touchegg -b -f
Compatible device detected:
  [...]
  Calculating threshold and animation_finish_threshold. You can tune this values in your service file
  threshold: 3
  animation_finish_threshold: 15
```


# FAQ

#### Does Touchégg work on Wayland?

No, Touchégg only works on X11.

#### What hardware is supported?

Under the hood, Touchégg relies on [libinput](https://wayland.freedesktop.org/libinput/doc/latest/index.html).

All hardware supported by libinput is supported by Touchégg.

#### Is there a GUI to configure Touchégg?

Yes, [Touché](https://github.com/JoseExposito/touche) is the official desktop application.

#### Can I use 2 finger swipes for web browser navigation?

No, at least not with Touchégg. It is up to the web browser to implement that feature.
You can request this feature in your favourite's web browser bug tracker.

# Copyright

Copyright 2011 - 2021 José Expósito <<jose.exposito89@gmail.com>>

The source code is available under GPL v3 license on [GitHub](https://github.com/JoseExposito/touchegg)

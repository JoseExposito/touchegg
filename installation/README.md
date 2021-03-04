# Installation Files

## touchegg.conf - _Touchégg configuration file_

This file handles all of the default gestures on installing Touchégg.

## touchegg.desktop - _Touchégg application XDG desktop entry file_

This file contains a combination of meta information resources and a shortcut to the Touchégg application, in accordance with the [XDG Desktop Entry specification](https://specifications.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html) which defines a standard for applications to integrate into application menus of desktop environments.

This file is installed into the system-wide XDG Autostart directory (`/etc/xdg/autostart`), which allows autostarting ordinary desktop entries on desktop environment startup.

## touchegg.service.in - _Touchégg systemd service_

This service runs Touchégg in daemon mode (`touchegg --daemon`) as part of the "input" group.
The daemon will open a Unix domain socket so any service (usually `touchegg --client`) can have access to libinput's multi-touch gestures.

CMake configures the path for ExecStart and saves the result in `touchegg.service`.

### Learn more about systemd
https://wiki.archlinux.org/index.php/Systemd#Basic_systemctl_usage

### Installation
```bash
sudo cp installation/touchegg.service /lib/systemd/system
sudo systemctl enable touchegg.service
sudo systemctl start touchegg
systemctl status touchegg
journalctl -u touchegg -b -f  # Monitor the logs since last boot
```

### Debugging
Change the ExecStart to your binary path:

```
ExecStart=/home/jose/Devel/touchegg/build/touchegg --daemon
```

Copy the service file and restart it:

```bash
sudo systemctl daemon-reload && sudo systemctl restart touchegg
```

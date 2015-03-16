# Ubuntu 11.04 Natty Narwhal #

In Natty isn't necessary make any change in your configuration, only install and run Touchégg.



# Ubuntu 10.10 Maverick Meerkat #

## General configuration ##

Normally, Touchégg configuration, consists in change your touchpad configuration
to use evdev driver and _restart X._

Doing this is as simple as go to your /usr/share/X11/xorg.conf.d/ path and check
if exists any file like "nn-<trackpad name>.conf".

Copy this configuration to the end of /etc/X11/xorg.conf changing the
Driver "<driver name>" line to Driver "evdev".

If the /etc/X11/xorg.conf doesn't exist create it:
$ sudo touch /etc/X11/xorg.conf


## Specific configuration ##

  * **Apple Magic Trackpad:**

> Simply edit the /usr/share/X11/xorg.conf.d/60-magictrackpad.conf file and
> change the driver to evdev:
```
 # Apple Magic Trackpad
 Section "InputClass"
      Identifier "Magic Trackpad"
      MatchUSBID "05ac:030e"
      Driver "evdev"
 EndSection
```
> All gestures are detected and works fine.



  * **Asus eeepc 1000h (Buildin Elantech Trackpad)**

> The original settings can be seen in /usr/share/X11/xorg.conf.d/50-synaptics.conf
> Copy it to the end of /etc/X11/xorg.conf changing the driver to "evdev":
```
 Section "InputClass"
    Identifier "touchpad catchall"
    Driver "evdev"
    MatchIsTouchpad "on"
    MatchDevicePath "/dev/input/event*"
 EndSection
```
> Not support more than three fingers gestures.

> (Thanks [mbuess](http://code.google.com/p/touchegg/issues/detail?id=3)!)


  * **MacBook Pro 7.1**

> [Nils Schmidt](https://code.google.com/p/touchegg/issues/detail?id=19#c10) has written
> [an excellent article in his blog](http://infiniteblogging.co.cc/ubuntu-10-10-on-macbook-pro-7-1/#touchpad)
> explaining how to install Ubuntu in a MacBook Pro 7.1, Touchégg included.

> Basically is necessary add this lines to the end of /etc/X11/xorg.conf:
```
 Section "InputClass"
        Identifier "touchpad catchall"
        Driver "evdev"
        MatchIsTouchpad "on"
        MatchDevicePath "/dev/input/event*"
 EndSection
```

  * **Other MacBook's (MacBook, MacBook Pro, MacBook Air)**

> As say me ["jlcleary87"](http://code.google.com/p/touchegg/issues/detail?id=12)
> Touchégg is compatible with all aluminium MacBook's and configuration is
> similar to the Magic trackpad configuration.

> Thanks jlcleary87!

  * **Acer Aspire One D255**

> Only copy the content of"10-evdev.conf" in your /etc/X11/xorg.conf:
```
 Section "InputClass"
        Identifier "evdev touchpad catchall"
        MatchIsTouchpad "on"
        MatchDevicePath "/dev/input/event*"
        Driver "evdev"
 EndSection
```
> You can see the full issue [here](http://code.google.com/p/touchegg/issues/detail?id=34)
> and a complete article with videos
> [here (in spanish)](http://equimantux.wordpress.com/2011/03/21/instalar-probar-y-configirar-touchegg-en-un-acer-one-d255-con-ubuntu/).

  * **HP Pavilon DV6000**

> As [Virgolus](http://code.google.com/p/touchegg/issues/detail?id=32) said me  is necesary copy
> the content of /usr/share/X11/xorg.conf.d/50-synaptics.conf into /etc/X11/xorg.conf:
```
 Section "InputClass"
    Identifier "touchpad catchall"
    Driver "evdev"
    MatchIsTouchpad "on"
    MatchDevicePath "/dev/input/event*"
 EndSection
```


**Is my device supported by Touchégg?**
> Touchégg makes use of uTouch. The list of supported hardware by uTouch is available in the [Ubuntu Wiki](https://wiki.ubuntu.com/Multitouch/HardwareSupport).
> Another easy way to test if your device is supported is open a terminal and run Touchégg ($ touchegg). If you perform gestures and your device is supported, the information about it will appear.

**I'm using Unity and I can't use gestures with 3 and 4 fingers**
> Unity reserves to itself gestures with 3 and 4 gestures making impossible to Touchégg make use of it.

**There is a GUI available to configure Touchégg?**
> Yes, check out [Touchégg-GCE](https://github.com/Raffarti/Touchegg-gce).
> In addition you can check this wiki pages to configure your device:
> http://code.google.com/p/touchegg/wiki/AllGestures
> http://code.google.com/p/touchegg/wiki/AllActions

**What configuration need my multitouch device?**
> In Ubuntu 10.10 Mavarick Meerkat [this configuration is necessary](http://code.google.com/p/touchegg/wiki/ConfigureDevices).

> In later versions no configuration is required.

> In Precise, if you want to use gestures with 2 and 3 fingers, you need to follow this instructions:
> https://wiki.ubuntu.com/Multitouch/TouchpadSupport

> Yo can simply execute this commands to allow Touchégg to use this gestures:
```
  synclient TapButton2=0
  synclient TapButton3=0
  synclient ClickFinger2=0
  synclient ClickFinger3=0
  synclient HorizTwoFingerScroll=0
  synclient VertTwoFingerScroll=0
```

I personally recommend the use of synaptics to manage gestures with 1 and 2 fingers (left click, right click and two fingers scroll) and Touchégg to manage your personalized gestures with 3 or more fingers. To see how to configure synaptics:
http://uselessuseofcat.com/?p=74
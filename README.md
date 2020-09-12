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

Maximize a window. If it is already maximized, restore it.

Options:

| Option | Values | Description |
| - | - | - |
| animate | `true`/`false` | Set it to `true` to display the animation. `false` otherwise. |
| color | Hex color | Color of the animation. For example: `909090` |
| borderColor | Hex color | Border color of the animation. For example: `#FFFFFF` |

Example:

```
<gesture type="DRAG" fingers="3" direction="UP">
  <action type="MAXIMIZE_RESTORE_WINDOW">
    <animate>true</animate>
    <color>3E9FED</color>
    <borderColor>3E9FED</borderColor>
  </action>
</gesture>
```

![Animation](.github/images/MAXIMIZE_RESTORE_WINDOW.gif)


# Compilation and installation:

Follow the instructions available in the [HACKING.md](HACKING.md) file.

# Copyright:

Copyright 2011 - 2020 José Expósito <<jose.exposito89@gmail.com>>

The source code is available under GPL v2 license on [GitHub](https://github.com/JoseExposito/touchegg)

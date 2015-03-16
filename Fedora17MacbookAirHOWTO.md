(Thanks to Dan Lavu for this wiki page!)

Fedora 17 Macbook Air Touchegg HOWTO

I've successfully EFI booted my Macbook air and used Touchegg to get full gesture support and I love it. Gestures are the only reason I own an Apple product, it even got to the point that I'm using a touchpad for my main workstation at home but it's also a Wacom tablet and I do a lot of sketching in my free time, made the justification of buying it a little easier. The docs and current wiki online have basic instructions but it never worked for me, took a little bit of hacking and debugging but it works like a charm now.

I personally wanted a one and two finger click versus tap. The touchpad is sensitive so with taps it would happen all the time as I was casually browsing the web. Another difficult thing was hi-lighting text in a document. Personally I do not use the double single click and drag method to hi-lighting text, I prefer the click and (second finger) drag like a traditional mouse. If you have no ideas what I'm talking about try it, hi-light the italicized portion of this paragraph. Did you double-click, hold down and drag all with the same finger or did you click and use your second finger to scroll? Now you start seeing the dilemma, using Touchegg for two finger  gestures interferes with this.

My configuration is setup to do the following;
No single or double finger taps
Two finger vertical and horizontal drag for scrolling
Three finger horizontal swipes for back and forth on websites
Three finger vertical swipes to switch fedora desktops
Four finger for window dragging and snapping.
Five finger pinch to get to the application menu

Now for the meat and potatoes, I mean really how often do you really read the content in a HOWTO or just jump to the commands and steps? I'm not a writer and I despise writing documentation so I have to add silly or witty remarks in the docs to make it entertaining for myself, so you guys just deal with it. =D


Go ahead and add silfreed repo
Note: I was unable to find a public key for the repo so you have to ignore the gpg check. I always set repos to disabled and only pull the packages when I want.

Edit /etc/yum.repo.d/silfreed.repo and add the folllowing;
```
[silfreed] 
name=Silfreed $releasever - $basearch - Touchegg
baseurl=ftp://ftp.silfreed.net/repo/fedora/17/i386/silfreednet/ # Change arch if you are on x64
enabled=1 
gpgcheck=0 
# touchegg 
```

yum install touchegg –enablerepo=silfreed –nogpgcheck -y

First drop the following text in the touchegg configuration file ~/.config/touchegg/touchegg.conf

```
<touchégg> 
    <settings> 
        <property name="composed_gestures_time">1</property> 
    </settings> 
    

    <application name="All"> 
       <gesture type="DRAG" fingers="2" direction="ALL"> 
            <action type="SCROLL">SPEED=1:INVERTED=false</action> 
        </gesture> 

        <gesture type="TAP" fingers="2" direction=""> 
            <action type="MOUSE_CLICK">BUTTON=3</action> 
        </gesture> 
       <gesture type="TAP" fingers="3" direction=""> 
            <action type="MOUSE_CLICK">BUTTON=2</action> 
        </gesture> 
       <gesture type="DRAG" fingers="3" direction="UP"> 
            <action type="CHANGE_DESKTOP">PREVIOUS</action> 
        </gesture> 
       <gesture type="DRAG" fingers="3" direction="DOWN"> 
            <action type="CHANGE_DESKTOP">NEXT</action> 
        </gesture> 
       <gesture type="DRAG" fingers="3" direction="RIGHT"> 
            <action type="CHANGE_VIEWPORT">PREVIOUS</action> 
        </gesture> 
       <gesture type="DRAG" fingers="3" direction="LEFT"> 
            <action type="CHANGE_VIEWPORT">NEXT</action> 
        </gesture> 
       <gesture type="DRAG" fingers="4" direction="UP"> 
            <action type="MAXIMIZE_RESTORE_WINDOW"></action> 
        </gesture> 
        <gesture type="DRAG" fingers="4" direction="LEFT"> 
            <action type="MOVE_WINDOW"></action> 
        </gesture> 
        <gesture type="DRAG" fingers="4" direction="RIGHT"> 
            <action type="MOVE_WINDOW"></action> 
        </gesture> 
       <gesture type="PINCH" fingers="4" direction="ALL"> 
            <action type="RESIZE_WINDOW"></action> 
        </gesture> 
        <gesture type="PINCH" fingers="5" direction="ALL"> 
            <action type="SEND_KEYS">Alt+F1</action> 
        </gesture> 
   </application> 


    <application name="Okular, Gwenview"> 
       <gesture type="PINCH" fingers="2" direction="IN"> 
            <action type="SEND_KEYS">Control+KP_Add</action> 
        </gesture> 
       <gesture type="PINCH" fingers="2" direction="OUT"> 
            <action type="SEND_KEYS">Control+KP_Subtract</action> 
        </gesture> 
       <gesture type="ROTATE" fingers="2" direction="LEFT"> 
            <action type="SEND_KEYS">Control+L</action> 
        </gesture> 
       <gesture type="ROTATE" fingers="2" direction="RIGHT"> 
            <action type="SEND_KEYS">Control+R</action> 
        </gesture> 
   </application> 


    <application name="Chromium-browser, Dolphin, Firefox"> 
       <gesture type="DRAG" fingers="3" direction="RIGHT"> 
            <action type="SEND_KEYS">Alt+Left</action> 
        </gesture> 
       <gesture type="DRAG" fingers="3" direction="LEFT"> 
            <action type="SEND_KEYS">Alt+Right</action> 
        </gesture> 
    </application> 
</touchégg> 
```

Next lets add some parameters to xorg.conf, create /etc/X11/xorg.conf.d/60-touchpad.conf and drop the following text in;

```
Section "InputClass" 
        Identifier "touchpad catchall" 
        Driver "synaptics" 
        MatchIsTouchpad "on" 
        MatchDevicePath "/dev/input/event*" 
EndSection 

# This option enables the bottom right corner to be a right button on 
# non-synaptics clickpads. 
# This option is only interpreted by clickpads. 
Section "InputClass" 
        Identifier "Default clickpad buttons" 
        MatchDriver "synaptics" 
        Option "SoftButtonAreas" "50% 0 82% 0 0 0 0 0" 
EndSection 

# This option disables software buttons on Apple touchpads. 
# This option is only interpreted by clickpads. 
Section "InputClass" 
        Identifier "Disable clickpad buttons on Apple touchpads" 
        MatchProduct "Apple|bcm5974" 
        MatchDriver "synaptics" 
        Option "SoftButtonAreas" "0 0 0 0 0 0 0 0" 
	Option "ClickFinger3" "0" 
	Option "PalmDetect" "1" 
EndSection 

# Quirks for special touchpads 

# Force clickpad on for wireless trackpad. The propbit isn't set on 3.3. 
# Remove once we're on 3.4 
Section "InputClass" 
        Identifier "Disable clickpad buttons on Apple touchpads" 
        MatchProduct "Apple Wireless Trackpad" 
        MatchDriver "synaptics" 
        Option "ClickPad" "on" 
EndSection 

# Some devices have the buttons as part of the lower edge of the 
# touchpad.  Pressing a button moves the cursor, causing cursor jumps and 
# erroneous clicks. 
# Use the synaptics area property to work around this, udev labels these 
# devices for us as touchpad_button_overlap. 
# Affected: Dell Mini 
Section "InputClass" 
        Identifier "touchpad button overlap" 
        MatchIsTouchpad "on" 
        MatchTag "touchpad_button_overlap" 
        Option "AreaBottomEdge" "4000" 
EndSection 
```

Restart X, what this does is adding conditions to the Apple touchpad, most importantly Option "ClickFinger3" "0". This is disabling three finger taps recognition to be handled by Synaptics. You can do this manually by running the following commands.

```
synclient  ClickFinger3=0
synclient  TapButton3
```

You can find additional configuration parameters by running synclient but do not forget to add it to xorg.conf so it retains your settings.

Parameter settings:
```
    LeftEdge                = -3791 
    RightEdge               = 4311 
    TopEdge                 = 423 
    BottomEdge              = 6027 
    FingerLow               = 25 
    FingerHigh              = 30 
    FingerPress             = 257 
    MaxTapTime              = 180 
    MaxTapMove              = 522 
    MaxDoubleTapTime        = 180 
    SingleTapTimeout        = 180 
    ClickTime               = 100 
    FastTaps                = 0 
    EmulateMidButtonTime    = 0 
    EmulateTwoFingerMinZ    = 283 
    EmulateTwoFingerMinW    = 7 
    VertScrollDelta         = 237 
    HorizScrollDelta        = 237 
    VertEdgeScroll          = 0 
    HorizEdgeScroll         = 0 
    CornerCoasting          = 0 
    VertTwoFingerScroll     = 1 
    HorizTwoFingerScroll    = 1 
    MinSpeed                = 1 
    MaxSpeed                = 1.75 
    AccelFactor             = 0.0168549 
    TrackstickSpeed         = 40 
    EdgeMotionMinZ          = 30 
    EdgeMotionMaxZ          = 160 
    EdgeMotionMinSpeed      = 1 
    EdgeMotionMaxSpeed      = 949 
    EdgeMotionUseAlways     = 0 
    TouchpadOff             = 0 
    LockedDrags             = 0 
    LockedDragTimeout       = 5000 
    RTCornerButton          = 0 
    RBCornerButton          = 0 
    LTCornerButton          = 0 
    LBCornerButton          = 0 
    TapButton1              = 0 
    TapButton2              = 0 
    TapButton3              = 0 
    ClickFinger1            = 1 
    ClickFinger2            = 3 
    ClickFinger3            = 0 
    CircularScrolling       = 0 
    CircScrollDelta         = 0.1 
    CircScrollTrigger       = 0 
    CircularPad             = 0 
    PalmDetect              = 1 
    PalmMinWidth            = 10 
    PalmMinZ                = 200 
    CoastingSpeed           = 20 
    CoastingFriction        = 50 
    PressureMotionMinZ      = 30 
    PressureMotionMaxZ      = 160 
    PressureMotionMinFactor = 1 
    PressureMotionMaxFactor = 1 
    GrabEventDevice         = 1 
    TapAndDragGesture       = 1 
    AreaLeftEdge            = 0 
    AreaRightEdge           = 0 
    AreaTopEdge             = 0 
    AreaBottomEdge          = 0 
    HorizHysteresis         = 5 
    VertHysteresis          = 3 
    ClickPad                = 1 
    RightButtonAreaLeft     = 0 
    RightButtonAreaRight    = 0 
    RightButtonAreaTop      = 0 
    RightButtonAreaBottom   = 0 
    MiddleButtonAreaLeft    = 0 
    MiddleButtonAreaRight   = 0 
    MiddleButtonAreaTop     = 0 
    MiddleButtonAreaBottom  = 0 
```

Goto system settings and the touchpad configuration and make sure it looks like the following.



We're almost done now. Create /etc/gdm/PostLogin/Default and add touchegg &.  Now restart X. After you login gestures should be working only over an application.

Go application and advance settings and make sure have file manage desktop is enabled and that's it, everything should be working. Try a 5 finger pinch on a blank desktop to be certain.
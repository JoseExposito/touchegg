# Introduction #

In this page you can find a full list of the actions supported by Touchégg.

In addition you can see how to configure it editing the configuration file:

```
~/.config/touchegg/touchegg.conf
```

Remember that is not necessary to edit this file, you can change the Touchégg
configuration easily using the Touchégg-GUI application.


# List of actions #

| **NAME** | **SETTINGS** | **DESCRIPTION** |
|:---------|:-------------|:----------------|
|MOUSE\_CLICK | BUTTON=1..9 | Emulates the mouse. The BUTTON setting means:<br> 1 – Left button click <br> 2 – Middle button click <br> 3 – Right button click <br> 8 – Go backward<br> 9 – Go forward <br>
<tr><td> DRAG_AND_DROP </td><td> BUTTON=1..3 </td><td> Allow to make a drag&drop with any mouse button. The configuration is similar to the MOUSE_CLICK settings </td></tr>
<tr><td> SCROLL </td><td> SPEED=1..10:INVERTED=true/false </td><td> Emulates the vertical scroll. The SPEED setting means:<br>1 – Slow<br>10 – Fast<br><br>The INVERTED settings means:<br>true – Inverted scroll, for touchscreens<br>false – Non inverted scroll, for trackpads </td></tr>
<tr><td> SEND_KEYS </td><td> Key1+Key2+KeyN </td><td> Emulates a shortcut. You can use two types of keys:<br>Those who are pressed during the keyboard shortcut:<br>  - Shift<br>  - Control<br>  - Super<br>  - Alt<br>  - AltGR<br> <br> Those who are pressed in between, you can see the full list in the file /usr/include/X11/keysymdef.h. You must use it withput the "XK<code>_</code>" prefix.<br><br>For example: <code>&lt;action&gt;type="SEND_KEYS"&gt;Super+W&lt;/action&gt;</code></td></tr>
<tr><td> MINIMIZE_WINDOW </td><td> - </td><td> Minimizes the window under the cursor </td></tr>
<tr><td> MAXIMIZE_RESTORE_WINDOW </td><td> - </td><td> Maximizes or restores the window under the cursor </td></tr>
<tr><td> CLOSE_WINDOW </td><td> - </td><td> Closes the window under the cursor </td></tr>
<tr><td> RESIZE_WINDOW </td><td> - </td><td> Resizes the window under the cursor. Is necessary make this action with a PINCH gesture </td></tr>
<tr><td> MOVE_WINDOW </td><td> - </td><td> Moves the window under the cursor </td></tr>
<tr><td> SHOW_DESKTOP </td><td> - </td><td> In the first execution shows the desktop, in the second execution restores all windows. </td></tr>
<tr><td> CHANGE_DESKTOP </td><td> NEXT/PREVIOUS </td><td> Changes to the next or previous desktop </td></tr>
<tr><td> CHANGE_VIEWPORT </td><td> NEXT/PREVIOUS </td><td> Changes to the next or previous viewport </td></tr>
<tr><td> RUN_COMMAND </td><td> Command to run </td><td> Runs the specified command </td></tr>
# Extending functionality

Touchégg supports plugins that can be used to extend its functionality to suit your needs. This is done with a simple
scripting API that you can use in a shared library, meaning you are not limited to specific functionality. Each
extension interfaces with the Touchégg core through three main functions, of which, none are required.

## API

### `void gesture_start()`

Once the user initiates the gesture, this function will be called. It indicates the beginning of the gesture, and can be
used to initiate or launch certain tasks or activities.

### `void animate(double percentage)`

This function is called when ever the user updates the gesture, for instance in a swiping gesture, the fingers have been
moved, but not yet lifted.

`double percentage` A 0-1 value representing the level of completion of the gesture. Calculated as an offset from the
origin.

### void `gesture_end()`

Called once the user lifts their fingers off the touchpad or touch surface. Internally, this function is called to
invoke the gesture's action, for instance, the window's minimise function is called in here.

> **Note** What happens in these functions is at the discretion of the author, and you should take extreme care when using plugins that you have not compiled or written yourself.

## Compiling

Compiling is very straight-forward. Using the compiler of your choice, compile as a shared library. Using g++ gives the
example below

```bash
g++ -shared -fPIC -o libexample.so example.cpp -Wall -Wextra
```

It is important to follow the naming conventions of shared libraries, to ensure they are picked up correctly. Libraries
should be named `lib<name>.so`
# Compilation

Before you start coding, you will need to install some dependencies:

```
$ sudo apt-get install git build-essential gdb cmake \
  libudev-dev libinput-dev libpugixml-dev libcairo2-dev libx11-dev libxtst-dev libxrandr-dev
```

Now clone the source code and compile it following the usual CMake compilation steps:

```
$ git clone https://github.com/JoseExposito/touchegg.git
$ cd touchegg
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make -j$(nproc)
```

# Installation

After building the source code, you can install Touchégg by running this commands:

```
$ sudo make install
$ sudo systemctl daemon-reload && sudo systemctl restart touchegg # Start the daemon
$ touchegg # Run Touchégg
```

In addition, you can generate a Debian package and install it:

```
$ cpack -G DEB
$ sudo dpkg -i touchegg_*.deb # Install the package
$ sudo apt -f install # Install missing dependencies
$ touchegg # Run Touchégg
```

# Code Style

This project follows Google C++ Style Guide:

https://google.github.io/styleguide/cppguide.html

And uses clang-format, clang-tidy and `cpplint.py` automatically to check potential the code issues.

In order to take advantage of those tools, install the following dependencies:

```
$ sudo apt-get install clang clang-format clang-tidy python2
```

More information about `cpplint.py`:

https://google.github.io/styleguide/cppguide.html#cpplint

# Development environment

You can use any text editor or IDE. But, if like me, you are using Visual Studio Code, here are some
tips:

## C/C++ Extension

Install this extension for language support:

https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

## CMake Tools

Install this extension for CMake integration:

https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools

## EditorConfig Extension

Install this extension to override your preferences following the rules described in .editorconfig:

https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig

## Code Spell Checker Extension

Install this extension to avoid typos:

https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker


## Line Length

Google C++ Style Guide defines a limit of 80 characters:

https://google.github.io/styleguide/cppguide.html#Line_Length

In order to easily follow this rule, add the following configuration to your settings.json file by
pressing "Control + Shift + P" and typing "Preferences: Open Settings (JSON)":

```
"[cpp]": {
    "editor.rulers": [
        80
    ]
}
```

## Apply format on save

The best way to follow the code style rules is to let Visual Studio Code apply them for you.
add the following configuration to your settings.json file by
pressing "Control + Shift + P" and typing "Preferences: Open Settings (JSON)":

```
"editor.formatOnSave": true
```

# Understanding the Code:

The entire code is documented with Doxygen. If want to see this documentation in HTML format execute
the following commands:

```
$ cd documentation
$ doxygen doxyfile
```

The `./documentation/html/index.html` file is a good place to start.

Touchégg makes intensive use of libinput, don't forget to check its documentation:

https://wayland.freedesktop.org/libinput/doc/latest/index.html

https://wayland.freedesktop.org/libinput/doc/latest/api/

Xlib and X11 standards are also heavily used to manipulate the user desktop and windows:

Xlib: https://tronche.com/gui/x/xlib/

ICCCM: https://www.x.org/releases/X11R7.6/doc/xorg-docs/specs/ICCCM/icccm.html

EWMH: https://specifications.freedesktop.org/wm-spec/wm-spec-1.3.html

# Contact the developer:

If you want to report a bug or ask a question, you can do it in the official bug tracker:

https://github.com/JoseExposito/touchegg/issues

Happy coding!

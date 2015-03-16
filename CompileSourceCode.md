# Introduction #

In the [Downloads](https://code.google.com/p/touchegg/wiki/Downloads?tm=2) tab
you can see two types of files, DEB packages and source code.

In general, download DEB package will be most suitable for most users, since
allows easy  installation and uninstallation, usually just a double click.

However there may be other users such as developers, users with an architecture
which is not available a DEB package or just curious users, who want to compile
the source code.


# How to compile source code? #

Compile the source code is very simple, just follow these three steps:

  * 1 - [Download](https://code.google.com/p/touchegg/wiki/Downloads?tm=2) and unzip the source code:
  * 2 - Install Touchégg dependencies. In Ubuntu 11.10 Oneiric Ocelot and recent open a terminal and type:
```
 $ sudo apt-get build-dep touchegg
```
> If your are using a previous Ubuntu version or other distro these are the required packages:
```
 $ sudo apt-get install build-essential libqt4-dev utouch libgeis-dev libx11-6 libxtst-dev
```
  * 3 - Compile and install Touchégg:
```
 $ qmake
 $ make
 $ sudo make install
```
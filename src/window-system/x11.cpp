/**
 * Copyright 2011 - 2022 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#include "window-system/x11.h"

#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xrandr.h>
#include <cairo-xlib.h>

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "window-system/x11-cairo-surface.h"

X11::X11() {
  this->display = XOpenDisplay(nullptr);

  if (this->display == nullptr) {
    throw std::runtime_error{
        "Error opening your X11 display. "
        "Make sure your DISPLAY environment variable is set"};
  }
}

X11::~X11() {
  if (this->display != nullptr) {
    XCloseDisplay(this->display);
  }
}

std::string X11::getConnectionName() const {
  return XDisplayString(this->display);
}

std::unique_ptr<WindowT> X11::getWindowUnderCursor() const {
  Window rootWindow = None;
  Window childWindow = None;
  int rootX = 0;
  int rootY = 0;
  int childX = 0;
  int childY = 0;
  unsigned int mask = 0;
  int success = XQueryPointer(this->display, XDefaultRootWindow(this->display),
                              &rootWindow, &childWindow, &rootX, &rootY,
                              &childX, &childY, &mask);

  if (success == True && childWindow == None) {
    return std::make_unique<X11WindowT>(rootWindow);
  }

  Window topLevelWindow = this->getTopLevelWindow(childWindow);
  return std::make_unique<X11WindowT>(topLevelWindow);
}

std::string X11::getWindowClassName(const WindowT &window) const {
  std::string className;

  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return className;
  }

  XClassHint *classHint = XAllocClassHint();
  int status = XGetClassHint(this->display, x11Window.window, classHint);

  if (status == 0) {
    return className;
  }

  if (classHint->res_class != nullptr) {
    className = classHint->res_class;
    XFree(classHint->res_class);
  }

  if (classHint->res_name != nullptr) {
    XFree(classHint->res_name);
  }

  XFree(classHint);
  return className;
}

Rectangle X11::getWindowSize(const WindowT &window) const {
  Rectangle size;

  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return size;
  }

  XWindowAttributes attrs;
  Status status = XGetWindowAttributes(this->display, x11Window.window, &attrs);
  if (status == 0) {
    return size;
  }

  size.x = attrs.x;
  size.y = attrs.y;
  size.width = attrs.width;
  size.height = attrs.height;

  int x = 0;
  int y = 0;
  Window child = None;
  Bool translated = XTranslateCoordinates(this->display, x11Window.window,
                                          XDefaultRootWindow(this->display), 0,
                                          0, &x, &y, &child);
  if (translated == False) {
    return size;
  }

  size.x = x;
  size.y = y;

  Rectangle decoration = this->getWindowDecorationSize(x11Window.window);
  size.x += decoration.x;
  size.y += decoration.y;
  size.width -= decoration.width;
  size.height -= decoration.height;

  return size;
}

template <typename T>
std::vector<T> X11::getWindowProperty(Window window,
                                      const std::string &atomName,
                                      Atom atomType) const {
  std::vector<T> propertiesVector;

  Atom atom = XInternAtom(this->display, atomName.c_str(), True);
  if (atom == None) {
    return propertiesVector;
  }

  long offset = 0;        // NOLINT
  long offsetSize = 100;  // NOLINT
  Atom atomRet = None;
  int size = 0;
  unsigned long numItems = 0;          // NOLINT
  unsigned long bytesAfterReturn = 0;  // NOLINT
  unsigned char *ret = nullptr;
  int status = 0;

  do {
    status = XGetWindowProperty(this->display, window, atom, offset, offsetSize,
                                False, atomType, &atomRet, &size, &numItems,
                                &bytesAfterReturn, &ret);
    if (status == Success) {
      auto properties = reinterpret_cast<T *>(ret);  // NOLINT
      for (int i = 0; i < numItems; i++) {
        propertiesVector.push_back(properties[i]);  // NOLINT
      }
      XFree(ret);
      offset += offsetSize;
    }
  } while (status == Success && bytesAfterReturn != 0 && numItems != 0);

  return propertiesVector;
}

void X11::sendEvent(Window targetWindow, Window eventWidow,
                    const std::string &atomName,
                    const std::vector<unsigned long> &data) const {  // NOLINT
  XClientMessageEvent event;
  event.window = eventWidow;
  event.type = ClientMessage;
  event.message_type = XInternAtom(this->display, atomName.c_str(), False);
  event.format = 32;

  for (int n = 0; n < data.size(); n++) {
    event.data.l[n] = data.at(n);  // NOLINT
  }

  XSendEvent(this->display, targetWindow, False,
             (SubstructureNotifyMask | SubstructureRedirectMask),
             reinterpret_cast<XEvent *>(&event));  // NOLINT
  XFlush(this->display);
}

Window X11::getTopLevelWindow(Window window) const {
  // Get the list of top-level windows from the atom stored in the root window
  std::vector<Window> topLevelWindows = this->getWindowProperty<Window>(
      XDefaultRootWindow(this->display), "_NET_CLIENT_LIST", XA_WINDOW);

  // Figure out to which top-level window "window" belongs to
  auto pair = this->findTopLevelWindowInChildren(window, topLevelWindows);
  Window topLevelWindow = pair.second;
  return topLevelWindow;
}

std::pair<bool, Window> X11::findTopLevelWindowInChildren(
    Window window, const std::vector<Window> &topLevelWindows) const {
  // If "window" is in the "topLevelWindows" return it
  if (std::find(topLevelWindows.begin(), topLevelWindows.end(), window) !=
      topLevelWindows.end()) {
    return std::make_pair(true, window);
  }

  // Otherwise, find the top level window in the "window" children
  Window root = None;
  Window parent = None;
  Window *children = nullptr;
  unsigned int numChildren = 0;

  int status = XQueryTree(this->display, window, &root, &parent, &children,
                          &numChildren);
  if (status == 0) {
    return std::make_pair(true, None);
  }

  Window ret = None;
  bool found = false;
  int index = 0;
  while (!found && index < numChildren) {
    auto pair = this->findTopLevelWindowInChildren(children[index],  // NOLINT
                                                   topLevelWindows);
    found = pair.first;
    ret = pair.second;
    index++;
  }

  if (children != nullptr) {
    XFree(children);
  }

  return std::make_pair(found, ret);
}

bool X11::isWindowMaximized(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return false;
  }

  Atom atomMaxVert =
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_VERT", True);
  Atom atomMaxHorz =
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_HORZ", True);
  std::vector<Atom> states =
      this->getWindowProperty<Atom>(x11Window.window, "_NET_WM_STATE", XA_ATOM);

  bool maxHor = false;
  bool maxVert = false;
  for (Atom atom : states) {
    if (atom == atomMaxVert) {
      maxVert = true;
    }
    if (atom == atomMaxHorz) {
      maxHor = true;
    }
  }

  bool maximized = maxHor && maxVert;
  return maximized;
}

bool X11::isWindowFullscreen(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return false;
  }

  Atom atomFullscreen =
      XInternAtom(this->display, "_NET_WM_STATE_FULLSCREEN", True);
  std::vector<Atom> states =
      this->getWindowProperty<Atom>(x11Window.window, "_NET_WM_STATE", XA_ATOM);

  bool fullscreen = false;
  for (Atom atom : states) {
    if (atom == atomFullscreen) {
      fullscreen = true;
    }
  }

  return fullscreen;
}

bool X11::isSystemWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return false;
  }

  std::vector<Atom> types = this->getWindowProperty<Atom>(
      x11Window.window, "_NET_WM_WINDOW_TYPE", XA_ATOM);

  // Window type is not always set, but let's be optimistic
  if (types.empty()) {
    return false;
  }

  Atom normal = XInternAtom(this->display, "_NET_WM_WINDOW_TYPE_NORMAL", False);
  return (std::find(types.begin(), types.end(), normal) == types.end());
}

void X11::maximizeOrRestoreWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  std::vector<unsigned long> data;  // NOLINT
  data.push_back(2);                // _NET_WM_STATE_TOGGLE = 2
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_VERT", False));
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False));

  this->sendEvent(XDefaultRootWindow(this->display), x11Window.window,
                  "_NET_WM_STATE", data);
}

void X11::toggleFullscreenWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  std::vector<unsigned long> data;  // NOLINT
  data.push_back(2);                // _NET_WM_STATE_TOGGLE = 2
  data.push_back(XInternAtom(this->display, "_NET_WM_STATE_FULLSCREEN", False));

  this->sendEvent(XDefaultRootWindow(this->display), x11Window.window,
                  "_NET_WM_STATE", data);
}

void X11::minimizeWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  // Minimize the window
  this->sendEvent(XDefaultRootWindow(this->display), x11Window.window,
                  "WM_CHANGE_STATE", {IconicState});
}

Rectangle X11::minimizeWindowIconSize(const WindowT &window) const {
  Rectangle size;

  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return size;
  }

  // NOLINTNEXTLINE
  std::vector<unsigned long> iconSize = this->getWindowProperty<unsigned long>(
      x11Window.window, "_NET_WM_ICON_GEOMETRY", XA_CARDINAL);
  if (iconSize.size() < 4) {
    return size;
  }

  size.x = iconSize[0];
  size.y = iconSize[1];
  size.width = iconSize[2];
  size.height = iconSize[3];
  return size;
}

void X11::tileWindow(const WindowT &window, bool toTheLeft) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  Window rootWindow = XDefaultRootWindow(this->display);

  // Window can not be maximized
  std::vector<unsigned long> data;  // NOLINT
  data.push_back(0);                // _NET_WM_STATE_REMOVE = 0
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_VERT", False));
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False));
  this->sendEvent(rootWindow, x11Window.window, "_NET_WM_STATE", data);

  // Move and resize the window
  Rectangle maxSize = this->getDesktopWorkarea();
  unsigned long x = toTheLeft  // NOLINT
                        ? maxSize.x
                        : maxSize.x + (maxSize.width / 2);
  unsigned long y = maxSize.y;                // NOLINT
  unsigned long width = (maxSize.width / 2);  // NOLINT
  unsigned long height = maxSize.height;      // NOLINT

  Rectangle decoration = this->getWindowDecorationSize(x11Window.window);
  x -= decoration.x;
  y -= decoration.y;
  width += decoration.width;
  height += decoration.height;

  this->sendEvent(
      rootWindow, x11Window.window, "_NET_MOVERESIZE_WINDOW",
      {StaticGravity | (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 15),
       x, y, width, height});
}

void X11::activateWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  // NOLINTNEXTLINE
  std::vector<unsigned long> data{
      1,  // Should be 1 when the request comes from an application
      CurrentTime,
      0  // Requestor's currently active window, 0 if none
  };

  this->sendEvent(XDefaultRootWindow(this->display), x11Window.window,
                  "_NET_ACTIVE_WINDOW", data);
}

void X11::closeWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  // NOLINTNEXTLINE
  std::vector<unsigned long> data{
      CurrentTime,
      1,  // Should be 1 when the request comes from an application
  };

  this->sendEvent(XDefaultRootWindow(this->display), x11Window.window,
                  "_NET_CLOSE_WINDOW", data);
}

void X11::sendKeys(const std::vector<std::string> &keycodes,
                   bool isPress) const {
  for (const std::string &keycode : keycodes) {
    KeySym sym = XStringToKeysym(keycode.c_str());
    KeyCode code = XKeysymToKeycode(this->display, sym);

    if (sym != 0 && code != 0) {
      XTestFakeKeyEvent(this->display, code, isPress ? True : False, 0);
    } else {
      std::cout << "Error performing keyboard shortcut. Unknown key: "
                << keycode << std::endl;
    }
  }

  XFlush(this->display);
}

void X11::sendMouseClick(int button) const {
  XTestFakeButtonEvent(this->display, button, True, 0);
  XTestFakeButtonEvent(this->display, button, False, 0);
  XFlush(this->display);
}

Rectangle X11::getDesktopWorkarea() const {
  // When multiple physical screens are connected, the root window's size is the
  // sum of all of them. Use Xrandr to get the screen size of the physical
  // screens the mouse pointer is placed on in order to display the animation
  // there
  Window rootWindow = None;
  Window childWindow = None;
  int pointerX = 0;
  int pointerY = 0;
  int childX = 0;
  int childY = 0;
  unsigned int mask = 0;
  XQueryPointer(this->display, XDefaultRootWindow(this->display), &rootWindow,
                &childWindow, &pointerX, &pointerY, &childX, &childY, &mask);

  // Get the physical screen size the mouse pointer is placed on
  bool screenFound = false;
  Rectangle screen;
  int currentCrtc = 0;
  XRRScreenResources *resources =
      XRRGetScreenResources(this->display, rootWindow);

  while (!screenFound && currentCrtc < resources->ncrtc) {
    XRRCrtcInfo *crtc =
        // NOLINTNEXTLINE
        XRRGetCrtcInfo(this->display, resources, resources->crtcs[currentCrtc]);

    if (pointerX >= crtc->x && pointerX < (crtc->x + crtc->width) &&
        pointerY >= crtc->y && pointerY < (crtc->y + crtc->height)) {
      screenFound = true;
      screen.x = crtc->x;
      screen.y = crtc->y;
      screen.width = static_cast<int>(crtc->width);
      screen.height = static_cast<int>(crtc->height);
    }

    XRRFreeCrtcInfo(crtc);
    currentCrtc++;
  }

  XRRFreeScreenResources(resources);

  // Get the workarea. Notice that this size applies to the root window, ie, the
  // sum of all physical screens
  std::vector<unsigned long> currenDesktop =   // NOLINT
      this->getWindowProperty<unsigned long>(  // NOLINT
          rootWindow, "_NET_CURRENT_DESKTOP", XA_CARDINAL);
  // NOLINTNEXTLINE
  std::vector<unsigned long> workareas = this->getWindowProperty<unsigned long>(
      rootWindow, "_NET_WORKAREA", XA_CARDINAL);

  Rectangle workarea;

  if (workareas.size() >= 4) {
    workarea.x = workareas[0 + (currenDesktop[0] * 4)];
    workarea.y = workareas[1 + (currenDesktop[0] * 4)];
    workarea.width = workareas[2 + (currenDesktop[0] * 4)];
    workarea.height = workareas[3 + (currenDesktop[0] * 4)];
  } else {
    // Some WMs don't set _NET_WORKAREA if there are no visible panels
    // https://github.com/JoseExposito/touchegg/issues/381
    unsigned int width = 0;
    unsigned int height = 0;
    Window retRootWindow = None;
    unsigned int retBorderWidth = 0;
    unsigned int retDepth = 0;
    XGetGeometry(display, rootWindow, &retRootWindow, &workarea.x, &workarea.y,
                 &width, &height, &retBorderWidth, &retDepth);
    workarea.width = static_cast<int>(width);
    workarea.height = static_cast<int>(height);
  }

  // Mutter uses a non standard property that allow better multiscreen support
  if (screenFound) {
    // NOLINTNEXTLINE
    std::vector<unsigned long> gtkWorkareas =
        this->getWindowProperty<unsigned long>(  // NOLINT
            rootWindow, "_GTK_WORKAREAS_D" + std::to_string(currenDesktop[0]),
            XA_CARDINAL);
    if (gtkWorkareas.size() >= 4) {
      int offset = 0;
      while (offset < gtkWorkareas.size()) {
        int x = gtkWorkareas[0 + offset];
        int y = gtkWorkareas[1 + offset];
        int width = gtkWorkareas[2 + offset];
        int height = gtkWorkareas[3 + offset];
        if (x >= screen.x && x < (screen.x + screen.width) && y >= screen.y &&
            y < (screen.y + screen.height)) {
          workarea.x = x;
          workarea.y = y;
          workarea.width = width;
          workarea.height = height;
        }
        offset += 4;
      }
    }
  }

  // Transform the workarea size to the physical screen size
  if (screenFound) {
    int x = std::max(workarea.x, screen.x);
    int y = std::max(workarea.y, screen.y);
    int width =
        std::min(workarea.x + workarea.width, screen.x + screen.width) - x;
    int height =
        std::min(workarea.y + workarea.height, screen.y + screen.height) - y;

    workarea.x = x;
    workarea.y = y;
    workarea.width = width;
    workarea.height = height;
  }

  return workarea;
}

void X11::changeDesktop(ActionDirection direction, bool cyclic) const {
  Window rootWindow = XDefaultRootWindow(this->display);

  // NOLINTNEXTLINE
  std::vector<unsigned long> total = this->getWindowProperty<unsigned long>(
      rootWindow, "_NET_NUMBER_OF_DESKTOPS", XA_CARDINAL);
  // NOLINTNEXTLINE
  std::vector<unsigned long> current = this->getWindowProperty<unsigned long>(
      rootWindow, "_NET_CURRENT_DESKTOP", XA_CARDINAL);

  if (total.size() != 1 || current.size() != 1) {
    return;
  }

  int totalDesktops = total.front();
  int currentDesktop = current.front();

  int toDesktop = -1;
  switch (direction) {
    case ActionDirection::UP:
    case ActionDirection::DOWN:
    case ActionDirection::LEFT:
    case ActionDirection::RIGHT:
      toDesktop =
          this->destinationDesktop(currentDesktop, totalDesktops, direction);
      break;
    case ActionDirection::NEXT:
      toDesktop = cyclic ? (currentDesktop + 1) % totalDesktops
                         : std::min(totalDesktops - 1, currentDesktop + 1);
      break;
    case ActionDirection::PREVIOUS:
    default:
      int prev = currentDesktop - 1;
      toDesktop = cyclic
                      ? (prev % totalDesktops + totalDesktops) % totalDesktops
                      : std::max(0, prev);
      break;
  }

  if (toDesktop < 0) {
    return;
  }

  this->sendEvent(rootWindow, rootWindow, "_NET_CURRENT_DESKTOP",
                  {static_cast<unsigned long>(toDesktop)});  // NOLINT
}

int X11::destinationDesktop(int currentDesktop, int totalDesktops,
                            ActionDirection direction) const {
  int toDestop = -1;
  Window rootWindow = XDefaultRootWindow(this->display);
  // NOLINTNEXTLINE
  std::vector<unsigned long> layout = this->getWindowProperty<unsigned long>(
      rootWindow, "_NET_DESKTOP_LAYOUT", XA_CARDINAL);

  if (layout.size() < 3) {
    return toDestop;
  }

  int columns = layout[1];

  switch (direction) {
    case ActionDirection::UP:
      if (currentDesktop >= columns) {
        toDestop = currentDesktop - columns;
      }
      break;
    case ActionDirection::DOWN:
      if (currentDesktop < totalDesktops - columns) {
        toDestop = currentDesktop + columns;
      }
      break;
    case ActionDirection::LEFT:
      if (currentDesktop > (std::floor(currentDesktop / columns) * columns)) {
        toDestop = currentDesktop - 1;
      }
      break;
    case ActionDirection::RIGHT:
      if (currentDesktop <
          std::min(
              totalDesktops - 1,
              static_cast<int>(std::floor(currentDesktop / columns) * columns +
                               columns - 1))) {
        toDestop = currentDesktop + 1;
      }
      break;
    default:
      break;
  }

  return toDestop;
}

void X11::showDesktop(bool show) const {
  Window rootWindow = XDefaultRootWindow(this->display);
  this->sendEvent(rootWindow, rootWindow, "_NET_SHOWING_DESKTOP",
                  {show ? 1UL : 0UL});
}

bool X11::isShowingDesktop() const {
  std::vector<unsigned long> showingDesktop =  // NOLINT
      this->getWindowProperty<unsigned long>(  // NOLINT
          XDefaultRootWindow(this->display), "_NET_SHOWING_DESKTOP",
          XA_CARDINAL);

  if (showingDesktop.empty()) {
    return false;
  }

  return (showingDesktop.at(0) != 0);
}

Rectangle X11::getWindowDecorationSize(Window window) const {
  Rectangle size;
  // NOLINTNEXTLINE
  std::vector<unsigned long> gtk = this->getWindowProperty<unsigned long>(
      window, "_GTK_FRAME_EXTENTS", XA_CARDINAL);
  if (gtk.size() == 4) {
    size.x += gtk[0];
    size.y += gtk[2];
    size.width += static_cast<int>(gtk[0] + gtk[1]);
    size.height += static_cast<int>(gtk[2] + gtk[3]);
  }

  // NOLINTNEXTLINE
  std::vector<unsigned long> frame = this->getWindowProperty<unsigned long>(
      window, "_NET_FRAME_EXTENTS", XA_CARDINAL);
  if (frame.size() == 4) {
    size.x -= frame[0];
    size.y -= frame[2];
    size.width -= static_cast<int>(frame[0] + frame[1]);
    size.height -= static_cast<int>(frame[2] + frame[3]);
    return size;
  }

  // NOLINTNEXTLINE
  std::vector<unsigned long> kde = this->getWindowProperty<unsigned long>(
      window, "_KDE_NET_WM_FRAME_STRUT", XA_CARDINAL);
  if (kde.size() == 4) {
    size.x -= kde[0];
    size.y -= kde[2];
    size.width -= static_cast<int>(kde[0] + kde[1]);
    size.height -= static_cast<int>(kde[2] + kde[3]);
    return size;
  }

  return size;
}

std::unique_ptr<CairoSurface> X11::createCairoSurface() const {
  return std::make_unique<X11CairoSurface>(this->display);
}

bool X11::isNaturalScrollEnabled(DeviceType deviceType) const {
  if (deviceType == DeviceType::TOUCHSCREEN) {
    return true;
  }

  bool enabled = false;
  int currentDevice = 0;
  int nDevices = 0;
  XIDeviceInfo *devices = XIQueryDevice(this->display, XIAllDevices, &nDevices);

  while (!enabled && currentDevice < nDevices) {
    XIDeviceInfo info = devices[currentDevice];  // NOLINT

    if (info.use == XIMasterPointer || info.use == XISlavePointer) {
      // Only touchpads have this property. I wasn't able to find a better way
      // to differentiate between mice and touchpads. Without this check,
      // enabilling natural scroll on the mouse but not on the touchpad will
      // make this method return true.
      // It seems like the same flag is used by GTK:
      // https://gitlab.gnome.org/GNOME/gtk/-/blob/4.0.0/gdk/x11/gdkdevicemanager-xi2.c#L452
      std::vector<unsigned char> touchpad =
          this->getDeviceProperty<unsigned char>(
              info.deviceid, "libinput Tapping Enabled", XA_INTEGER);
      bool isTouchpad = (touchpad.size() == 1);

      if (isTouchpad) {
        std::vector<unsigned char> naturalScroll =
            this->getDeviceProperty<unsigned char>(
                info.deviceid, "libinput Natural Scrolling Enabled",
                XA_INTEGER);
        enabled = (naturalScroll.size() == 1 && naturalScroll[0] != 0);
      }
    }

    currentDevice++;
  }

  XIFreeDeviceInfo(devices);
  return enabled;
}

GestureDirection X11::calculateRotation(GestureType gestureType,
                                        DeviceType deviceType,
                                        GestureDirection direction) const {
  if (gestureType != GestureType::SWIPE ||
      deviceType != DeviceType::TOUCHSCREEN) {
    return direction;
  }

  // Use Xrandr to get the screen rotation of the physical screen the mouse
  // pointer is placed on
  Window rootWindow = None;
  Window childWindow = None;
  int pointerX = 0;
  int pointerY = 0;
  int childX = 0;
  int childY = 0;
  unsigned int mask = 0;
  XQueryPointer(this->display, XDefaultRootWindow(this->display), &rootWindow,
                &childWindow, &pointerX, &pointerY, &childX, &childY, &mask);

  // Get the physical screen size the mouse pointer is placed on
  bool screenFound = false;
  Rotation rotation = 0;
  int currentCrtc = 0;
  XRRScreenResources *resources =
      XRRGetScreenResources(this->display, rootWindow);

  while (!screenFound && currentCrtc < resources->ncrtc) {
    XRRCrtcInfo *crtc =
        // NOLINTNEXTLINE
        XRRGetCrtcInfo(this->display, resources, resources->crtcs[currentCrtc]);

    if (pointerX >= crtc->x && pointerX < (crtc->x + crtc->width) &&
        pointerY >= crtc->y && pointerY < (crtc->y + crtc->height)) {
      screenFound = true;
      rotation = crtc->rotation;
    }

    XRRFreeCrtcInfo(crtc);
    currentCrtc++;
  }

  XRRFreeScreenResources(resources);

  if (!screenFound) {
    return direction;
  }

  GestureDirection rotatedDirection = direction;
  switch (rotation) {
    case RR_Rotate_90:
      if (direction == GestureDirection::UP) {
        rotatedDirection = GestureDirection::RIGHT;
      } else if (direction == GestureDirection::DOWN) {
        rotatedDirection = GestureDirection::LEFT;
      } else if (direction == GestureDirection::LEFT) {
        rotatedDirection = GestureDirection::UP;
      } else if (direction == GestureDirection::RIGHT) {
        rotatedDirection = GestureDirection::DOWN;
      }
      break;
    case RR_Rotate_180:
      if (direction == GestureDirection::UP) {
        rotatedDirection = GestureDirection::DOWN;
      } else if (direction == GestureDirection::DOWN) {
        rotatedDirection = GestureDirection::UP;
      } else if (direction == GestureDirection::LEFT) {
        rotatedDirection = GestureDirection::RIGHT;
      } else if (direction == GestureDirection::RIGHT) {
        rotatedDirection = GestureDirection::LEFT;
      }
      break;
    case RR_Rotate_270:
      if (direction == GestureDirection::UP) {
        rotatedDirection = GestureDirection::LEFT;
      } else if (direction == GestureDirection::DOWN) {
        rotatedDirection = GestureDirection::RIGHT;
      } else if (direction == GestureDirection::LEFT) {
        rotatedDirection = GestureDirection::DOWN;
      } else if (direction == GestureDirection::RIGHT) {
        rotatedDirection = GestureDirection::UP;
      }
      break;
    case RR_Rotate_0:
    default:
      break;
  }

  return rotatedDirection;
}

template <typename T>
std::vector<T> X11::getDeviceProperty(int deviceId, const std::string &atomName,
                                      Atom atomType) const {
  std::vector<T> propertiesVector;

  Atom atom = XInternAtom(this->display, atomName.c_str(), True);
  if (atom == None) {
    return propertiesVector;
  }

  long offset = 0;        // NOLINT
  long offsetSize = 100;  // NOLINT
  Atom atomRet = None;
  int size = 0;
  unsigned long numItems = 0;          // NOLINT
  unsigned long bytesAfterReturn = 0;  // NOLINT
  unsigned char *ret = nullptr;
  int status = 0;

  do {
    status = XIGetProperty(this->display, deviceId, atom, offset, offsetSize,
                           False, atomType, &atomRet, &size, &numItems,
                           &bytesAfterReturn, &ret);
    if (status == Success) {
      auto properties = reinterpret_cast<T *>(ret);  // NOLINT
      for (int i = 0; i < numItems; i++) {
        propertiesVector.push_back(properties[i]);  // NOLINT
      }
      XFree(ret);
      offset += offsetSize;
    }
  } while (status == Success && bytesAfterReturn != 0 && numItems != 0);

  return propertiesVector;
}

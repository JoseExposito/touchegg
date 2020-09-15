/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
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
#include <X11/extensions/XTest.h>
#include <cairo-xlib.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

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

std::unique_ptr<WindowT> X11::getWindowUnderCursor() const {
  Window rootWindow;
  Window childWindow;
  int rootX;
  int rootY;
  int childX;
  int childY;
  unsigned int mask;
  XQueryPointer(this->display, XDefaultRootWindow(this->display), &rootWindow,
                &childWindow, &rootX, &rootY, &childX, &childY, &mask);
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

  int x;
  int y;
  Window child;
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
  Atom atomRet;
  int size;
  unsigned long numItems;          // NOLINT
  unsigned long bytesAfterReturn;  // NOLINT
  unsigned char *ret;
  int status;

  do {
    status = XGetWindowProperty(this->display, window, atom, offset, offsetSize,
                                False, atomType, &atomRet, &size, &numItems,
                                &bytesAfterReturn, &ret);
    if (status == Success) {
      auto properties = reinterpret_cast<T *>(ret);  // NOLINT
      for (int i = 0; i < numItems; i++) {
        propertiesVector.push_back(properties[i]);
      }
      XFree(ret);
      offset += offsetSize;
    }
  } while (status == Success && bytesAfterReturn != 0 && numItems != 0);

  return propertiesVector;
}

void X11::sendEvent(Window targetWindow, Window eventWidow,
                    const std::string &atomName,
                    const std::vector<long> &data) const {  // NOLINT
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
  Window root;
  Window parent;
  Window *children;
  unsigned int numChildren;

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

  std::vector<long> data;  // NOLINT
  data.push_back(2);       // _NET_WM_STATE_TOGGLE = 2
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_VERT", False));
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False));

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

  std::vector<uint64_t> iconSize = this->getWindowProperty<uint64_t>(
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
  std::vector<long> data;  // NOLINT
  data.push_back(0);       // _NET_WM_STATE_REMOVE = 0
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_VERT", False));
  data.push_back(
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False));
  this->sendEvent(rootWindow, x11Window.window, "_NET_WM_STATE", data);

  // Move and resize the window
  Rectangle maxSize = this->getDesktopWorkarea();
  int x = toTheLeft ? maxSize.x : maxSize.x + (maxSize.width / 2);
  int y = maxSize.y;
  int width = (maxSize.width / 2);
  int height = maxSize.height;

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
  std::vector<long> data{
      1,  // Should be 1 when the request comes from an application
      CurrentTime,
      0  // Requestor's currently active window, 0 if none
  };

  this->sendEvent(XDefaultRootWindow(this->display), x11Window.window,
                  "_NET_ACTIVE_WINDOW", data);
}

void X11::sendKeys(const std::vector<std::string> &keycodes,
                   bool isPress) const {
  for (const std::string &keycode : keycodes) {
    KeySym sym = XStringToKeysym(keycode.c_str());
    KeyCode code = XKeysymToKeycode(this->display, sym);
    XTestFakeKeyEvent(this->display, code, isPress ? True : False, 0);
  }

  XFlush(this->display);
}

Rectangle X11::getDesktopWorkarea() const {
  // TODO(jose) When multiple physical screens are connected, the root
  // window's size is the sum of all of them. Use X11/extensions/Xrandr.h to
  // get the screen size of the window to animate in order to display the
  // animation in the correct screen.

  Window rootWindow = XDefaultRootWindow(this->display);

  std::vector<int> currenDesktop = this->getWindowProperty<int>(
      rootWindow, "_NET_CURRENT_DESKTOP", XA_CARDINAL);
  std::vector<uint64_t> workArea = this->getWindowProperty<uint64_t>(
      rootWindow, "_NET_WORKAREA", XA_CARDINAL);

  Rectangle size;
  size.x = workArea[0 + (currenDesktop[0] * 4)];
  size.y = workArea[1 + (currenDesktop[0] * 4)];
  size.width = workArea[2 + (currenDesktop[0] * 4)];
  size.height = workArea[3 + (currenDesktop[0] * 4)];
  return size;
}

void X11::changeDesktop(bool next) const {
  Window rootWindow = XDefaultRootWindow(this->display);

  std::vector<int32_t> total = this->getWindowProperty<int32_t>(
      rootWindow, "_NET_NUMBER_OF_DESKTOPS", XA_CARDINAL);
  std::vector<int32_t> current = this->getWindowProperty<int32_t>(
      rootWindow, "_NET_CURRENT_DESKTOP", XA_CARDINAL);

  if (total.size() != 1 || current.size() != 1) {
    return;
  }

  int32_t totalDesktops = total.front();
  int32_t currentDesktop = current.front();

  int32_t toDesktop = next ? std::min(totalDesktops - 1, currentDesktop + 1)
                           : std::max(0, currentDesktop - 1);

  this->sendEvent(rootWindow, rootWindow, "_NET_CURRENT_DESKTOP", {toDesktop});
}

void X11::showDesktop() const {
  Window rootWindow = XDefaultRootWindow(this->display);

  std::vector<bool> showingDesktop = this->getWindowProperty<bool>(
      rootWindow, "_NET_SHOWING_DESKTOP", XA_CARDINAL);

  if (showingDesktop.empty()) {
    return;
  }

  this->sendEvent(rootWindow, rootWindow, "_NET_SHOWING_DESKTOP",
                  {showingDesktop.at(0) ? False : True});
}

Rectangle X11::getWindowDecorationSize(Window window) const {
  Rectangle size;

  std::vector<uint64_t> decoration = this->getWindowProperty<uint64_t>(
      window, "_GTK_FRAME_EXTENTS", XA_CARDINAL);

  if (decoration.size() != 4) {
    return size;
  }

  size.x = decoration[0];
  size.y = decoration[2];
  size.width = (decoration[0] + decoration[1]);
  size.height = (decoration[2] + decoration[3]);

  return size;
}

cairo_surface_t *X11::createSurface() const {
  Window rootWindow = XDefaultRootWindow(this->display);
  int screen = XDefaultScreen(this->display);

  // Get the screen size. If multiple physical screens are connected this is
  // the size of all of them, like they were a single screen
  int x = 0;
  int y = 0;
  int width = XWidthOfScreen(XDefaultScreenOfDisplay(this->display));
  int height = XHeightOfScreen(XDefaultScreenOfDisplay(this->display));

  // Create a transparent window
  XVisualInfo vInfo;
  XMatchVisualInfo(this->display, screen, 32, TrueColor, &vInfo);

  XSetWindowAttributes attr;
  attr.colormap =
      XCreateColormap(this->display, rootWindow, vInfo.visual, AllocNone);
  attr.border_pixel = 0;
  attr.background_pixel = 0;
  attr.override_redirect = 1;

  Window window = XCreateWindow(
      this->display, rootWindow, x, y, width, height, 0, vInfo.depth,
      InputOutput, vInfo.visual,
      CWColormap | CWBorderPixel | CWBackPixel | CWOverrideRedirect, &attr);
  XMapWindow(display, window);

  // Create the surface
  cairo_surface_t *surface = cairo_xlib_surface_create(
      this->display, window, vInfo.visual, width, height);
  cairo_xlib_surface_set_size(surface, width, height);

  return surface;
}

int X11::getSurfaceWidth(cairo_surface_t *cairoSurface) const {
  return cairo_xlib_surface_get_width(cairoSurface);
}

int X11::getSurfaceHeight(cairo_surface_t *cairoSurface) const {
  return cairo_xlib_surface_get_height(cairoSurface);
}

void X11::flushSurface(cairo_surface_t * /*cairoSurface*/) const {
  XFlush(this->display);
}

void X11::destroySurface(cairo_surface_t *cairoSurface) const {
  Window window = cairo_xlib_surface_get_drawable(cairoSurface);
  cairo_surface_destroy(cairoSurface);
  XDestroyWindow(this->display, window);
  XFlush(this->display);
}

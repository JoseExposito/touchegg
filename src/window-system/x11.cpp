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
#include <cairo-xlib.h>

#include <algorithm>
#include <exception>
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

cairo_surface_t *X11::createSurface() const {
  Window rootWindow = XDefaultRootWindow(this->display);
  int screen = XDefaultScreen(this->display);

  // Get the current desktop size (without dock, panels, etc)
  std::vector<int> currenDesktop = this->getWindowProperty<int>(
      rootWindow, "_NET_CURRENT_DESKTOP", XA_CARDINAL);
  std::vector<uint64_t> workArea = this->getWindowProperty<uint64_t>(
      rootWindow, "_NET_WORKAREA", XA_CARDINAL);
  int x = workArea[0 + (currenDesktop[0] * 4)];
  int y = workArea[1 + (currenDesktop[0] * 4)];
  int width = workArea[2 + (currenDesktop[0] * 4)];
  int height = workArea[3 + (currenDesktop[0] * 4)];

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

void X11::maximizeOrRestoreWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  XClientMessageEvent event;
  event.window = x11Window.window;
  event.type = ClientMessage;
  event.message_type = XInternAtom(this->display, "_NET_WM_STATE", False);
  event.format = 32;
  event.data.l[0] = 2;  // _NET_WM_STATE_TOGGLE = 2  // NOLINT
  // NOLINTNEXTLINE
  event.data.l[1] =
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
  // NOLINTNEXTLINE
  event.data.l[2] =
      XInternAtom(this->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);

  XSendEvent(this->display, XDefaultRootWindow(this->display), False,
             (SubstructureNotifyMask | SubstructureRedirectMask),
             reinterpret_cast<XEvent *>(&event));  // NOLINT
  XFlush(this->display);
}

void X11::minimizeWindow(const WindowT &window) const {
  auto x11Window = dynamic_cast<const X11WindowT &>(window);
  if (x11Window.window == None) {
    return;
  }

  // Minimize the window
  XClientMessageEvent event;
  event.window = x11Window.window;
  event.type = ClientMessage;
  event.message_type = XInternAtom(this->display, "WM_CHANGE_STATE", False);
  event.format = 32;
  event.data.l[0] = IconicState;  // NOLINT

  XSendEvent(this->display, XDefaultRootWindow(this->display), False,
             (SubstructureNotifyMask | SubstructureRedirectMask),
             reinterpret_cast<XEvent *>(&event));  // NOLINT
  XFlush(this->display);
}

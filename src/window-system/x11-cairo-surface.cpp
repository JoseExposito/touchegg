/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
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
#include "window-system/x11-cairo-surface.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo-xlib.h>

#include <iostream>

X11CairoSurface::X11CairoSurface(Display *display) : display(display) {
  Window rootWindow = XDefaultRootWindow(this->display);
  int defaultScreen = XDefaultScreen(this->display);
  Screen *screenOfDisplay = XDefaultScreenOfDisplay(this->display);

  // Get the screen size. If multiple physical screens are connected this is
  // the size of all of them, like they were a single screen
  int x = 0;
  int y = 0;
  int width = XWidthOfScreen(screenOfDisplay);
  int height = XHeightOfScreen(screenOfDisplay);

  // Create a transparent window
  XVisualInfo vInfo;
  XMatchVisualInfo(this->display, defaultScreen, 32, TrueColor, &vInfo);

  XSetWindowAttributes attr;
  attr.colormap =
      XCreateColormap(this->display, rootWindow, vInfo.visual, AllocNone);
  attr.border_pixel = 0;
  attr.background_pixel = 0;
  attr.override_redirect = 1;

  this->window = XCreateWindow(
      this->display, rootWindow, x, y, width, height, 0, vInfo.depth,
      InputOutput, vInfo.visual,
      CWColormap | CWBorderPixel | CWBackPixel | CWOverrideRedirect, &attr);
  XMapWindow(display, this->window);

  // Create the window cairo surface and context
  this->windowSurface = cairo_xlib_surface_create(this->display, this->window,
                                                  vInfo.visual, width, height);
  cairo_xlib_surface_set_size(this->windowSurface, width, height);
  this->windowContext = cairo_create(this->windowSurface);

  // Create the image surface to draw in memory for double buffering
  this->imageSurface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  this->imageContext = cairo_create(this->imageSurface);
}

X11CairoSurface::~X11CairoSurface() {
  cairo_destroy(this->windowContext);
  cairo_destroy(this->imageContext);

  cairo_surface_destroy(this->windowSurface);
  cairo_surface_destroy(this->imageSurface);

  XDestroyWindow(this->display, this->window);
  XFlush(this->display);
}

cairo_t *X11CairoSurface::getContext() { return this->imageContext; }

void X11CairoSurface::flush() {
  // Draw the image context in the window surface
  cairo_surface_flush(this->imageSurface);
  cairo_set_source_rgba(this->windowContext, 0, 0, 0, 0);
  cairo_set_operator(this->windowContext, CAIRO_OPERATOR_SOURCE);
  cairo_set_source_surface(this->windowContext, this->imageSurface, 0, 0);
  cairo_paint(this->windowContext);
  cairo_surface_flush(this->windowSurface);
  XFlush(this->display);

  // Restore the context
  cairo_set_source_surface(this->windowContext, this->windowSurface, 0, 0);
  cairo_set_source_surface(this->imageContext, this->imageSurface, 0, 0);
}

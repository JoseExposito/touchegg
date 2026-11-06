/**
 * Copyright 2026 The Touchégg contributors
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
#ifndef WINDOW_SYSTEM_WAYLAND_CAIRO_SURFACE_H_
#define WINDOW_SYSTEM_WAYLAND_CAIRO_SURFACE_H_

#include <cairo.h>
#include <wayland-client.h>

#include <cstdint>
#include <string>
#include <vector>

#include "utils/rectangle.h"
#include "window-system/cairo-surface.h"
#include "window-system/wayland-connection.h"

struct zwlr_layer_surface_v1;

/**
 * Transparent, click-through overlay covering one output, used to draw the
 * animations. Animations draw using global (logical) coordinates, like on X11.
 */
class WaylandCairoSurface : public CairoSurface {
 public:
  /**
   * @param connection Connection to the compositor.
   * @param outputName Name of the output to draw on.
   * @param outputGeometry Logical geometry of the output in the global
   * coordinate space.
   */
  WaylandCairoSurface(WaylandConnection *connection,
                      const std::string &outputName,
                      const Rectangle &outputGeometry);
  ~WaylandCairoSurface() override;

  cairo_t *getContext() override;
  void flush() override;

 private:
  struct Buffer {
    wl_buffer *buffer = nullptr;
    void *data = nullptr;
    size_t size = 0;
    bool busy = false;
  };

  WaylandConnection *connection;
  wl_surface *surface = nullptr;
  zwlr_layer_surface_v1 *layerSurface = nullptr;
  bool configured = false;
  bool closed = false;
  int width = 0;
  int height = 0;
  int scale = 1;
  int stride = 0;
  Rectangle outputGeometry;

  cairo_surface_t *bufferSurface = nullptr;
  cairo_t *bufferContext = nullptr;
  std::vector<Buffer> buffers;

  Buffer *getFreeBuffer();
  void createDrawingSurface();

  static void onConfigure(void *data, zwlr_layer_surface_v1 *layerSurface,
                          uint32_t serial, uint32_t width, uint32_t height);
  static void onClosed(void *data, zwlr_layer_surface_v1 *layerSurface);
};

#endif  // WINDOW_SYSTEM_WAYLAND_CAIRO_SURFACE_H_

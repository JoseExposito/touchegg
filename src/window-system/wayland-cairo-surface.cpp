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
#include "window-system/wayland-cairo-surface.h"

#include <sys/mman.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "protocols/wlr-layer-shell-unstable-v1-client-protocol.h"
#include "utils/logger.h"

namespace {
// Keep at most this number of buffers in flight. If the compositor holds all
// of them, the frame is skipped
constexpr size_t MAX_BUFFERS = 3;

const wl_buffer_listener BUFFER_LISTENER = {
    [](void *data, wl_buffer * /*buffer*/) {
      *static_cast<bool *>(data) = false;
    },
};
}  // namespace

WaylandCairoSurface::WaylandCairoSurface(WaylandConnection *connection,
                                         const std::string &outputName,
                                         const Rectangle &outputGeometry)
    : connection(connection), outputGeometry(outputGeometry) {
  // Reserve the buffers so their addresses (used as listener data) are stable
  this->buffers.reserve(MAX_BUFFERS);

  if (connection->getLayerShell() == nullptr ||
      connection->getCompositor() == nullptr ||
      connection->getShm() == nullptr) {
    this->createDrawingSurface();
    return;
  }

  const WaylandConnection::Output *output = connection->findOutput(outputName);
  if (output != nullptr) {
    this->scale = output->scale;
  }

  this->surface = wl_compositor_create_surface(connection->getCompositor());

  // Click-through: empty input region
  wl_region *region = wl_compositor_create_region(connection->getCompositor());
  wl_surface_set_input_region(this->surface, region);
  wl_region_destroy(region);

  this->layerSurface = zwlr_layer_shell_v1_get_layer_surface(
      connection->getLayerShell(), this->surface,
      (output != nullptr) ? output->output : nullptr,
      ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY, "touchegg");

  static const zwlr_layer_surface_v1_listener layerSurfaceListener = {
      WaylandCairoSurface::onConfigure, WaylandCairoSurface::onClosed};
  zwlr_layer_surface_v1_add_listener(this->layerSurface, &layerSurfaceListener,
                                     this);

  // Cover the whole output, ignoring panels, so the surface origin matches
  // the output origin
  zwlr_layer_surface_v1_set_anchor(this->layerSurface,
                                   ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP |
                                       ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM |
                                       ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT |
                                       ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT);
  zwlr_layer_surface_v1_set_exclusive_zone(this->layerSurface, -1);
  zwlr_layer_surface_v1_set_size(this->layerSurface, 0, 0);
  // 0: No keyboard interactivity (the enum is missing in older protocol XMLs)
  zwlr_layer_surface_v1_set_keyboard_interactivity(this->layerSurface, 0);
  wl_surface_set_buffer_scale(this->surface, this->scale);
  wl_surface_commit(this->surface);

  connection->roundtrip();

  if (!this->configured) {
    tlg::error << "The compositor didn't configure the animation surface"
               << std::endl;
  }

  this->createDrawingSurface();
}

WaylandCairoSurface::~WaylandCairoSurface() {
  if (this->bufferContext != nullptr) {
    cairo_destroy(this->bufferContext);
  }
  if (this->bufferSurface != nullptr) {
    cairo_surface_destroy(this->bufferSurface);
  }

  if (this->layerSurface != nullptr) {
    zwlr_layer_surface_v1_destroy(this->layerSurface);
  }
  if (this->surface != nullptr) {
    wl_surface_destroy(this->surface);
  }

  for (Buffer &buffer : this->buffers) {
    wl_buffer_destroy(buffer.buffer);
    munmap(buffer.data, buffer.size);
  }

  wl_display_flush(this->connection->getDisplay());
}

cairo_t *WaylandCairoSurface::getContext() { return this->bufferContext; }

void WaylandCairoSurface::flush() {
  cairo_surface_flush(this->bufferSurface);

  this->connection->dispatchPending();
  if (!this->configured || this->closed) {
    return;
  }

  Buffer *buffer = this->getFreeBuffer();
  if (buffer == nullptr) {
    // The compositor is still using all the buffers, skip this frame
    return;
  }

  std::memcpy(buffer->data, cairo_image_surface_get_data(this->bufferSurface),
              buffer->size);
  buffer->busy = true;

  wl_surface_attach(this->surface, buffer->buffer, 0, 0);
  wl_surface_damage_buffer(this->surface, 0, 0, this->width * this->scale,
                           this->height * this->scale);
  wl_surface_commit(this->surface);
  wl_display_flush(this->connection->getDisplay());
}

WaylandCairoSurface::Buffer *WaylandCairoSurface::getFreeBuffer() {
  for (Buffer &buffer : this->buffers) {
    if (!buffer.busy) {
      return &buffer;
    }
  }

  if (this->buffers.size() >= MAX_BUFFERS) {
    return nullptr;
  }

  size_t size = static_cast<size_t>(this->stride) * this->height * this->scale;
  int fd = memfd_create("touchegg-animation", MFD_CLOEXEC);
  if (fd < 0 || ftruncate(fd, static_cast<off_t>(size)) != 0) {
    tlg::error << "Error allocating memory for the animation" << std::endl;
    if (fd >= 0) {
      close(fd);
    }
    return nullptr;
  }

  void *data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED) {
    close(fd);
    return nullptr;
  }

  wl_shm_pool *pool = wl_shm_create_pool(this->connection->getShm(), fd,
                                         static_cast<int32_t>(size));
  wl_buffer *wlBuffer = wl_shm_pool_create_buffer(
      pool, 0, this->width * this->scale, this->height * this->scale,
      this->stride, WL_SHM_FORMAT_ARGB8888);
  wl_shm_pool_destroy(pool);
  close(fd);

  this->buffers.push_back({wlBuffer, data, size, false});
  Buffer &buffer = this->buffers.back();
  wl_buffer_add_listener(buffer.buffer, &BUFFER_LISTENER, &buffer.busy);
  return &buffer;
}

void WaylandCairoSurface::createDrawingSurface() {
  if (this->width <= 0 || this->height <= 0) {
    // Not configured: draw off-screen so animations still work without
    // displaying anything
    this->width =
        this->outputGeometry.width > 0 ? this->outputGeometry.width : 1;
    this->height =
        this->outputGeometry.height > 0 ? this->outputGeometry.height : 1;
    this->scale = 1;
  }

  int pixelWidth = this->width * this->scale;
  int pixelHeight = this->height * this->scale;
  this->stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, pixelWidth);
  this->bufferSurface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, pixelWidth, pixelHeight);
  this->bufferContext = cairo_create(this->bufferSurface);

  // Animations use logical global coordinates
  cairo_scale(this->bufferContext, this->scale, this->scale);
  cairo_translate(this->bufferContext, -this->outputGeometry.x,
                  -this->outputGeometry.y);
}

void WaylandCairoSurface::onConfigure(void *data,
                                      zwlr_layer_surface_v1 *layerSurface,
                                      uint32_t serial, uint32_t width,
                                      uint32_t height) {
  auto *self = static_cast<WaylandCairoSurface *>(data);
  zwlr_layer_surface_v1_ack_configure(layerSurface, serial);

  // The size can't change after creating the cairo surface. It only changes
  // if the output is resized while the animation is running
  if (!self->configured) {
    self->width = static_cast<int>(width);
    self->height = static_cast<int>(height);
    self->configured = (width > 0 && height > 0);
  }
}

void WaylandCairoSurface::onClosed(void *data,
                                   zwlr_layer_surface_v1 * /*layerSurface*/) {
  static_cast<WaylandCairoSurface *>(data)->closed = true;
}

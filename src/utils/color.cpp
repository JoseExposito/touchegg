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
#include "utils/color.h"

#include <iostream>

#ifdef AUTO_COLORS
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#endif

Color::Color(const std::string &hexString, ColorType colorType) {
  if (hexString == "auto") {
    this->setFromAutoColor(colorType);
  } else {
    this->setFromHexString(hexString);
  }
}

void Color::setFromHexString(const std::string &hexString) {
  if (hexString.size() != 6 &&
      (hexString.size() != 7 && hexString.front() != '#')) {
    return;
  }

  size_t offset = (hexString.size() == 6) ? 0 : 1;

  try {
    this->red = std::stoi(hexString.substr(offset, 2), nullptr, 16) / 255.0;
    this->green =
        std::stoi(hexString.substr(offset + 2, 2), nullptr, 16) / 255.0;
    this->blue =
        std::stoi(hexString.substr(offset + 4, 2), nullptr, 16) / 255.0;
  } catch (const std::exception & /* error */) {
    std::cout << "Error: Invalid animation color, using default color"
              << std::endl;
  }
}

void Color::setFromAutoColor(ColorType colorType) {
#ifdef AUTO_COLORS
  gtk_init_check(nullptr, nullptr);
  while (gtk_events_pending()) {
    gtk_main_iteration_do(false);
  }

  GtkWidget *label = gtk_label_new("");
  g_object_ref_sink(label);
  GtkStyleContext *labelStyleContext = gtk_widget_get_style_context(label);
  GtkWidgetPath *path =
      gtk_widget_path_copy(gtk_style_context_get_path(labelStyleContext));
  gtk_widget_path_iter_set_object_name(path, -1, "selection");

  GtkStyleContext *colorStyleContext = gtk_style_context_new();
  gtk_style_context_set_path(colorStyleContext, path);
  gtk_style_context_set_parent(colorStyleContext, labelStyleContext);

  GdkRGBA *color;
  // NOLINTNEXTLINE
  gtk_style_context_get(
      colorStyleContext, GTK_STATE_FLAG_NORMAL,
      (colorType == ColorType::BACKGROUND ? GTK_STYLE_PROPERTY_BACKGROUND_COLOR
                                          : GTK_STYLE_PROPERTY_BORDER_COLOR),
      &color, nullptr);

  this->red = color->red;
  this->green = color->green;
  this->blue = color->blue;

  gdk_rgba_free(color);
  g_object_unref(colorStyleContext);
  gtk_widget_path_free(path);
  gtk_widget_destroy(label);
  g_object_unref(label);
#endif
}

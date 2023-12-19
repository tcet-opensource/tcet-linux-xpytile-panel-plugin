/*
 * Copyright (C) 2017 Marcin Kedzierski <marcin.kedzierski@gmx.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hello-plugin.h"

#include <gtk/gtk.h>
#include <libxfce4panel/libxfce4panel.h>
#include <libxfce4ui/libxfce4ui.h>

static void sample_construct(XfcePanelPlugin* plugin) {
    // Create your widgets here
    GtkWidget* widget = gtk_button_new_with_label("Click me!");

    // Connect your widgets to the plugin's menu
    xfce_panel_plugin_add_action_widget(plugin, widget);

    // If your plugin has a configuration dialog or an about dialog,
    // make the corresponding menu items visible and connect them to the
    // 'configure-plugin' and 'about' signals
    xfce_panel_plugin_menu_show_about(plugin);
    xfce_panel_plugin_menu_show_configure(plugin);

    // Add your widgets to the plugin's container
    gtk_container_add(GTK_CONTAINER(plugin), widget);
}

XFCE_PANEL_PLUGIN_REGISTER(sample_construct);

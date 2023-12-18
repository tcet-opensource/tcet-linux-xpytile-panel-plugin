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

#include <gtk/gtk.h>
#include <libxfce4panel/libxfce4panel.h>
#include <libxfce4ui/libxfce4ui.h>

class Plugin {
public:
  Plugin(XfcePanelPlugin *plugin) : plugin_(plugin) {
    label_ = gtk_label_new("Hello");
    gtk_widget_show(label_);

    box_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(box_), label_);
    gtk_widget_show(box_);

    gtk_container_add(GTK_CONTAINER(plugin_), box_);

  }

private:
  XfcePanelPlugin *plugin_;

  GtkWidget *box_;
  GtkWidget *label_;
};


typedef struct {
    XfcePanelPlugin* plugin;

    /* panel widgets */
    GtkWidget* ebox;
    GtkWidget* hvbox;
    GtkWidget* label;

    /* sample settings */
    gchar* setting1;
    gint setting2;
    gboolean setting3;
} SamplePlugin;

extern "C" void sample_configure(XfcePanelPlugin* plugin, SamplePlugin* sample) {
    GtkWidget* dialog;

    /* block the plugin menu */
    xfce_panel_plugin_block_menu(plugin);

    /* create the dialog */
    dialog = xfce_titled_dialog_new_with_buttons(
        _("Sample Plugin"),
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(plugin))),
        GTK_DIALOG_DESTROY_WITH_PARENT, "gtk-help", GTK_RESPONSE_HELP,
        "gtk-close", GTK_RESPONSE_OK, NULL);

    /* center dialog on the screen */
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    /* set dialog icon */
    gtk_window_set_icon_name(GTK_WINDOW(dialog), "xfce4-settings");

    /* link the dialog to the plugin, so we can destroy it when the plugin
     * is closed, but the dialog is still open */
    g_object_set_data(G_OBJECT(plugin), "dialog", dialog);

    /* connect the response signal to the dialog */
    // g_signal_connect(G_OBJECT(dialog), "response", sample);

    /* show the entire dialog */
    gtk_widget_show(dialog);
}


extern "C" void hello_construct(XfcePanelPlugin *);
static void hello_free(XfcePanelPlugin *, Plugin *);

extern "C" {
#include <libxfce4ui/libxfce4ui.h>
#include <libxfce4util/libxfce4util.h>
}

extern "C" void hello_construct(XfcePanelPlugin *plugin) {
  xfce_textdomain("Xpytile", PACKAGE_LOCALE_DIR, "UTF-8");
  new Plugin(plugin);

  g_signal_connect(plugin, "free-data", G_CALLBACK(hello_free), nullptr);
}

static void hello_free(XfcePanelPlugin *, Plugin *plugin) { delete plugin; }

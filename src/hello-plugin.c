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


static void sample_configure_response(GtkWidget* dialog, gint response,
                                      SamplePlugin* sample) {
    gboolean result;

    if (response == GTK_RESPONSE_HELP) {
        /* show help */
        result = g_spawn_command_line_async(
            "exo-open --launch WebBrowser " "www.google.com", NULL);

        if (G_UNLIKELY(result == FALSE))
            g_warning(_("Unable to open the following url: %s"),
                      "www.google.com");
    } else {
        /* remove the dialog data from the plugin */
        g_object_set_data(G_OBJECT(sample->plugin), "dialog", NULL);

        /* unlock the panel menu */
        xfce_panel_plugin_unblock_menu(sample->plugin);

        /* save the plugin */
        sample_save(sample->plugin, sample);

        /* destroy the properties dialog */
        gtk_widget_destroy(dialog);
    }
}

SamplePlugin* sample_new(XfcePanelPlugin* plugin) {
  SamplePlugin* sample;
  GtkOrientation orientation;
  GtkWidget* label;

  /* allocate memory for the plugin structure */
  sample = g_slice_new0(SamplePlugin);

  /* pointer to plugin */
  sample->plugin = plugin;

  /* get the current orientation */
  orientation = xfce_panel_plugin_get_orientation(plugin);

  /* create some panel widgets */
  sample->ebox = gtk_event_box_new();
  gtk_widget_show(sample->ebox);

  sample->hvbox = gtk_box_new(orientation, 2);
  gtk_widget_show(sample->hvbox);
  gtk_container_add(GTK_CONTAINER(sample->ebox), sample->hvbox);

  /* some sample widgets */
  label = gtk_label_new(_("Sample"));
  gtk_widget_show(label);
  gtk_box_pack_start(GTK_BOX(sample->hvbox), label, FALSE, FALSE, 0);

  label = gtk_label_new(_("Plugin"));
  gtk_widget_show(label);
  gtk_box_pack_start(GTK_BOX(sample->hvbox), label, FALSE, FALSE, 0);

  return sample;
}

void sample_configure(XfcePanelPlugin* plugin, SamplePlugin* sample) {
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
  g_signal_connect(G_OBJECT(dialog), "response",
                   G_CALLBACK(sample_configure_response), sample);

  /* show the entire dialog */
  gtk_widget_show(dialog);
}

static void sample_free(XfcePanelPlugin* plugin, SamplePlugin* sample) {
  GtkWidget* dialog;

  /* check if the dialog is still open. if so, destroy it */
  dialog = g_object_get_data(G_OBJECT(plugin), "dialog");
  if (G_UNLIKELY(dialog != NULL)) gtk_widget_destroy(dialog);

  /* destroy the panel widgets */
  gtk_widget_destroy(sample->hvbox);

  /* cleanup the settings */
  if (G_LIKELY(sample->setting1 != NULL)) g_free(sample->setting1);

  /* free the plugin structure */
  g_slice_free(SamplePlugin, sample);
}

void sample_save(XfcePanelPlugin* plugin, SamplePlugin* sample) {
  XfceRc* rc;
  gchar* file;

  /* get the config file location */
  file = xfce_panel_plugin_save_location(plugin, TRUE);

  if (G_UNLIKELY(file == NULL)) {
    DBG("Failed to open config file");
    return;
  }

  /* open the config file, read/write */
  rc = xfce_rc_simple_open(file, FALSE);
  g_free(file);

  if (G_LIKELY(rc != NULL)) {
    /* save the settings */
    DBG(".");
    if (sample->setting1) xfce_rc_write_entry(rc, "setting1", sample->setting1);

    xfce_rc_write_int_entry(rc, "setting2", sample->setting2);
    xfce_rc_write_bool_entry(rc, "setting3", sample->setting3);

    /* close the rc file */
    xfce_rc_close(rc);
  }
}

static void sample_construct(XfcePanelPlugin* plugin) {
  SamplePlugin* sample;

  /* setup transation domain */
  xfce_textdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");

  /* create the plugin */
  sample = sample_new(plugin);

  /* add the ebox to the panel */
  gtk_container_add(GTK_CONTAINER(plugin), sample->ebox);

  /* show the panel's right-click menu on this ebox */
  xfce_panel_plugin_add_action_widget(plugin, sample->ebox);

  /* connect plugin signals */
  g_signal_connect(G_OBJECT(plugin), "free-data", G_CALLBACK(sample_free),
                   sample);
  //
  g_signal_connect(G_OBJECT(plugin), "save", G_CALLBACK(sample_save), sample);
  //
  // g_signal_connect(G_OBJECT(plugin), "size-changed",
  //                  G_CALLBACK(sample_size_changed), sample);
  //
  // g_signal_connect(G_OBJECT(plugin), "orientation-changed",
  //                  G_CALLBACK(sample_orientation_changed), sample);
  //
  // /* show the configure menu item and connect signal */
  // xfce_panel_plugin_menu_show_configure(plugin);
  g_signal_connect(G_OBJECT(plugin), "configure-plugin",
                   G_CALLBACK(sample_configure), sample);
  //
  // /* show the about menu item and connect signal */
  // xfce_panel_plugin_menu_show_about(plugin);
  // g_signal_connect(G_OBJECT(plugin), "about", G_CALLBACK(sample_about),
  // NULL);
}

#ifndef __HELLO_H__
#define __HELLO_H__

#include "libxfce4panel/xfce-panel-plugin.h"
G_BEGIN_DECLS
/* plugin structure */
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

G_END_DECLS

#endif /* !__HELLO_H__ */

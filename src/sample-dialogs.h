/*  $Id$
 *
 *  Copyright (C) 2012 John Doo <john@foo.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __SAMPLE_DIALOGS_H__
#define __SAMPLE_DIALOGS_H__

#include "libxfce4panel/xfce-panel-plugin.h"
#include "sample.h"
G_BEGIN_DECLS

void sample_configure(XfcePanelPlugin* plugin, SamplePlugin* sample);

void sample_about(XfcePanelPlugin* plugin);

G_END_DECLS

#endif

/*
 * alarm-applet.h -- Alarm Clock applet bootstrap
 *
 * Copyright (C) 2007-2008 Johannes H. Jensen <joh@pseudoberries.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Authors:
 * 		Johannes H. Jensen <joh@pseudoberries.com>
 */

#ifndef ALARMAPPLET_H_
#define ALARMAPPLET_H_

#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <libxml/parser.h>

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <gdk/gdkkeysyms.h>
#include <gconf/gconf-client.h>
#include <gst/gst.h>

//#include <panel-applet.h>
//#include <panel-applet-gconf.h>

G_BEGIN_DECLS

typedef struct _AlarmApplet AlarmApplet;

gchar *supported_sound_mime_types[];
GHashTable *app_command_map;

void alarm_applet_label_update (AlarmApplet *applet);
void alarm_applet_clear_alarms (AlarmApplet *applet);

#include "alarm.h"
#include "prefs.h"
#include "alarm-gconf.h"
#include "player.h"
#include "util.h"
#include "list-entry.h"
#include "ui.h"

#define ALARM_NAME		 "Alarm Clock"
#define ALARM_ICON 		 "alarm-clock"
#define TIMER_ICON		 "alarm-timer"
#define ALARM_GCONF_DIR	 "/apps/alarm-clock"
#define ALARM_DEF_SNOOZE 9

#ifndef VERSION
#define VERSION "0.1"
#endif

typedef enum {
	LABEL_TYPE_INVALID = 0,
	LABEL_TYPE_TIME,
	LABEL_TYPE_REMAIN,
} LabelType;

struct _AlarmApplet {
    /* User Interface */
    GtkBuilder *ui;

	/* Status Icon */
	GtkStatusIcon *status_icon;
    GtkWidget *status_menu;
    
	/* Alarms */
	GList	*alarms;
    guint   n_triggered;        // Number of triggered alarms

	/* Sounds & apps list */
	GList *sounds;
	GList *apps;

	/* List-alarms UI */
	AlarmListWindow *list_window;

    /* Alarm settings dialog */
    AlarmSettingsDialog *settings_dialog;
    
	/* Preferences */
	GtkDialog *preferences_dialog;
    
    guint snooze_mins;

	/* GConf */
	guint listeners [N_GCONF_PREFS];
};

static void set_alarm_time (AlarmApplet *applet, guint hour, guint minute, guint second);
//static void time_changed_cb (GtkSpinButton *spinbutton, gpointer data);

void alarm_applet_sounds_load (AlarmApplet *applet);

void alarm_applet_apps_load (AlarmApplet *applet);

void alarm_applet_alarms_load (AlarmApplet *applet);

void alarm_applet_alarms_add (AlarmApplet *applet, Alarm *alarm);

void alarm_applet_alarms_remove (AlarmApplet *applet, Alarm *alarm);

guint alarm_applet_alarms_snooze (AlarmApplet *applet);

guint alarm_applet_alarms_stop (AlarmApplet *applet);

void alarm_applet_alarm_snooze (AlarmApplet *applet, Alarm *alarm);

void alarm_applet_alarm_stop (AlarmApplet *applet, Alarm *alarm);

void alarm_applet_destroy (AlarmApplet *applet);

G_END_DECLS

#endif /*ALARMAPPLET_H_*/

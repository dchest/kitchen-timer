#include <gtk/gtk.h>
#include <glib.h>

GtkWidget *window;
GtkWidget *box;
GtkWidget *start_btn;
GtkWidget *time_spin;

GTimer    *timer;
gdouble    time_goal;  /* how much time to count in seconds */
guint      timeout_id;

static void start_timer();
static void stop_timer();

static gboolean timeout_cb(gpointer data);
static void     start_stop_cb(GtkWidget *widget, gpointer data);
static void     destroy_cb(GtkWidget *widget, gpointer data);
static void     ding_dong();

static void
ding_dong()
{
	GtkWidget *dialog, *label, *content_area;
   
	gdk_beep(); /* TODO sound alert */
  
	/* Create the widgets */
	dialog = gtk_dialog_new_with_buttons("Message",
                                         GTK_WINDOW(window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_NONE,
                                         NULL);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	
	label = gtk_label_new("It's about time!");

	g_signal_connect_swapped (dialog,
                             "response",
                             G_CALLBACK(gtk_widget_destroy),
                             dialog);

	gtk_container_add(GTK_CONTAINER(content_area), label);
	gtk_widget_show_all(dialog);	
}

static gboolean
timeout_cb(gpointer data)
{
	gboolean rc = TRUE;
	gdouble   elapsed;   /* in seconds */
	
	gdk_threads_enter();
	if (timer != NULL) {
		elapsed = g_timer_elapsed(timer, NULL);
		/* g_print("elapsed: %f\n", elapsed); */
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(time_spin),
					  time_goal - elapsed);
		if (elapsed >= time_goal) {
			stop_timer(); /* we're done */
			ding_dong();
			rc = FALSE;
		}
	} else {
		rc = FALSE; /* don't call this cb anymore */
	}
	gdk_threads_leave();
	return (rc);
}

static void
start_timer()
{
	gdk_threads_enter();

	g_assert(timer == NULL);

	/* UI */
	gtk_widget_set_sensitive(GTK_WIDGET(time_spin), FALSE);
	gtk_button_set_label(GTK_BUTTON(start_btn), "Stop");
	
	/* Timer and timeout */
	time_goal = gtk_spin_button_get_value_as_float(
					GTK_SPIN_BUTTON(time_spin));
	timer = g_timer_new();
	g_timer_start(timer);
	g_timeout_add(500, timeout_cb, NULL); /* every 1/2 second */

	g_print("Timer started, goal: %f sec\n", time_goal);

	gdk_threads_leave();
}

static void
stop_timer()
{
	gdk_threads_enter();

	g_assert(timer != NULL);
	
	/* Timer */
	g_timer_destroy(timer);
	timer = NULL;

	/* UI */
	gtk_widget_set_sensitive(GTK_WIDGET(time_spin), TRUE);
	gtk_button_set_label(GTK_BUTTON(start_btn), "Start");
	g_print("Timer stopped\n");

	gdk_threads_leave();
}

static void
start_stop_cb(GtkWidget *widget, gpointer data)
{
	gdk_threads_enter();
	if (timer == NULL)
		start_timer();
	else
		stop_timer();
	gdk_threads_leave();
}

static void
destroy_cb(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

int
main(int argc, char *argv[])
{	
	gtk_init(&argc, &argv);
	
	/* Window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy_cb), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	/* Box */
	box = gtk_vbox_new(FALSE, 8);
	gtk_container_add(GTK_CONTAINER(window), box);
	
	/* Spin button with time */
	time_spin = gtk_spin_button_new_with_range(0, 360, 1);
	gtk_box_pack_start(GTK_BOX(box), time_spin, TRUE, TRUE, 0);
	
	/* Start button */
	start_btn = gtk_button_new_with_label("Start");
	g_signal_connect(start_btn, "clicked", G_CALLBACK(start_stop_cb),
			 NULL);
	gtk_box_pack_start(GTK_BOX(box), start_btn, TRUE, TRUE, 0);
	
	gtk_widget_show(time_spin);
	gtk_widget_show(start_btn);
	gtk_widget_show(box);
	gtk_widget_show(window);
	
	gtk_main();
	
	return (0);
}

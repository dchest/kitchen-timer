#include <gtk/gtk.h>

static void
start_cb(GtkWidget *widget, gpointer data)
{
	g_print("Timer started");
}

static void
destroy_cb(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

int
main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *start_btn;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy_cb), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	start_btn = gtk_button_new_with_label("Start");
	g_signal_connect(start_btn, "clicked", G_CALLBACK(start_cb), NULL);
	gtk_container_add(GTK_CONTAINER(window), start_btn);
	
	gtk_widget_show(start_btn);
	gtk_widget_show(window);
	
	gtk_main();
	
	return (0);
}

#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

static void on_popup_clicked (GtkButton*, GtkWidget*);
gboolean on_popup_focus_out (GtkWidget*, GdkEventFocus*, gpointer);


int main (int argc, char *argv[]) {
	GtkWidget *window, *button, *vbox, *spin, *label;
	GtkObject *adjustment;
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Parent window");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 600, 800);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	adjustment = gtk_adjustment_new(0, 0, 10, 1, 1, 0);
	label = gtk_label_new("INPUTS  ");
	
	vbox = gtk_vbox_new(0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
	spin = gtk_spin_button_new(GTK_ADJUSTMENT(adjustment), 1, 2);
	gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spin), 0);

	gtk_box_pack_start(GTK_BOX(vbox), spin, 0, 0, 0);	

	gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);
	g_signal_connect (G_OBJECT (spin), "value-changed", G_CALLBACK (on_popup_clicked), (gpointer) window);

	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}

void on_popup_clicked (GtkButton* widget, GtkWidget* pWindow) {
 	GtkWidget *popup_window;
	GtkWidget *entry;
	int inputs;
	inputs = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));

	popup_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (popup_window), "Pop Up window");
	gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
	gtk_window_set_resizable (GTK_WINDOW (popup_window), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (popup_window), TRUE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (popup_window), TRUE);
	gtk_window_set_skip_pager_hint (GTK_WINDOW (popup_window), TRUE);
	gtk_widget_set_size_request (popup_window, 600, 800);
	gtk_window_set_transient_for (GTK_WINDOW (popup_window), GTK_WINDOW (pWindow));
	gtk_window_set_position (GTK_WINDOW (popup_window), GTK_WIN_POS_CENTER);
	int columns, rows, ar[1024][10];
	int i, j, value;
	char str[10];
	GtkWidget *table, *label;

	table = gtk_table_new(1024, 11, 0);
	columns = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
	rows = pow(2, columns);

	for(i = 0; i < rows; i ++) {
		for(j = 0; j < columns; j ++)  {
			ar[i][j] = (i >> j) & 1;
			value = ar[i][columns - j - 1];
			sprintf(str, "%d", value);
							
			label = gtk_label_new(str);
			gtk_table_attach(GTK_TABLE(table), label, j, (j + 1), i, (i + 1), GTK_FILL, GTK_FILL, 50, 10);
		}
	}

	for(i = 0; i < rows; i ++) {
		entry = gtk_entry_new();
		gtk_table_attach(GTK_TABLE(table), entry, columns, (columns + 1), i, (i + 1), GTK_FILL, GTK_FILL, 50, 10);
	}		
	gtk_container_add(GTK_CONTAINER(popup_window), table);

	gtk_widget_set_events (popup_window, GDK_FOCUS_CHANGE_MASK);
	g_signal_connect (G_OBJECT (popup_window), "focus-out-event", G_CALLBACK (on_popup_focus_out), NULL);

	gtk_widget_show_all (popup_window);
	gtk_widget_grab_focus (popup_window);
}




gboolean on_popup_focus_out (GtkWidget *widget, GdkEventFocus *event, gpointer data) {
	gtk_widget_destroy (widget);
	return TRUE;
}

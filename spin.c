#include<gtk/gtk.h>
#include<stdio.h>
#include<math.h>
void value_changed(GtkWidget *widget, gpointer data) {
	g_print("%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget)));
}
int main(int argc, char* argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window, *spin, *hbox, *vbox, *label;
	GtkObject *adjustment;
	GtkWidget *widget[10][3];


	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	adjustment = gtk_adjustment_new(0, 0, 10, 1, 1, 0);
	label = gtk_label_new("INPUTS  ");
	
	vbox = gtk_vbox_new(0, 0);
	spin = gtk_spin_button_new(GTK_ADJUSTMENT(adjustment), 1, 2);
	gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spin), 0);

	g_signal_connect(spin, "value_changed", G_CALLBACK(value_changed), NULL);

	//gtk_container_add(GTK_CONTAINER(window), vbox);

	int i, j, rows, columns;
	rows = 10;
	columns = 4;
	vbox = gtk_vbox_new(0, 0);
	for(i = 0; i < rows; i ++) {
		hbox = gtk_hbox_new(0, 0);
		for(j = 0; j <= columns; j ++) {
			widget[i][j] = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(widget[i][j]), 1);
			gtk_widget_set_size_request(widget[i][j], 20, 20);
			gtk_box_pack_start(GTK_BOX(hbox), widget[i][j], 0, 0, 0);
		}
		gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);
	}
	gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), spin, 0, 0, 0);	
	gtk_container_add(GTK_CONTAINER(window), vbox);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

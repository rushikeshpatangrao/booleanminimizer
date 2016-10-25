#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main (int argc, char *argv[]) {
	GtkWidget *window;
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Parent window");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 600, 800);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	GtkWidget *menu_bar, *file_menu, *file_item, *new_item, *exit_item;
	GtkWidget *input_menu, *input_item, *truth_item, *minterm_item, *expression_item;
	file_menu = gtk_menu_new();

	menu_bar = gtk_menu_bar_new();
	new_item = gtk_menu_item_new_with_label("New");
	gtk_menu_append(GTK_MENU(file_menu), new_item);
	
	exit_item = gtk_menu_item_new_with_label("Exit");
	gtk_menu_append(GTK_MENU(file_menu), exit_item);

	file_item = gtk_menu_item_new_with_label("File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);

	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), file_item);
	

	input_menu = gtk_menu_new();

	truth_item = gtk_menu_item_new_with_label("Truth Table");
	gtk_menu_append(GTK_MENU(input_menu), truth_item);
	
	minterm_item = gtk_menu_item_new_with_label("Minterm");
	gtk_menu_append(GTK_MENU(input_menu), minterm_item);

	expression_item = gtk_menu_item_new_with_label("Expression");
	gtk_menu_append(GTK_MENU(input_menu), expression_item);

	input_item = gtk_menu_item_new_with_label("Input");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(input_item), input_menu);

	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), input_item);
	
	gtk_container_add(GTK_CONTAINER(window), menu_bar);		
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

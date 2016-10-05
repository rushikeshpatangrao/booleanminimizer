#include<gtk/gtk.h>
#include<string.h>

static void menu_pressed(GtkWidget *widget, gpointer data) {
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "New") == 0) {
		g_print("You pressed save\n");
	}
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Open") == 0) {
		g_print("You pressed new\n");
	}
	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Exit") == 0) {
		g_print("You pressed quit\n");
	}

	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "About") == 0) {
		g_print("You pressed about\n");
	}

	if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Help") == 0) {
		g_print("You pressed help\n");
	}

}

int main(int argc, char* argv[]) {
	GtkWidget *window;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *menu_bar, *menu_item, *file_menu, *help_menu, *vbox, *button, *label;

	
	vbox = gtk_vbox_new(0, 0);	
	menu_bar = gtk_menu_bar_new();
	file_menu = gtk_menu_new();
	help_menu = gtk_menu_new();

	menu_item = gtk_menu_item_new_with_label("file");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

	menu_item = gtk_menu_item_new_with_label("help");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), help_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);


	menu_item = gtk_menu_item_new_with_label("New");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(menu_pressed), NULL);

	menu_item = gtk_menu_item_new_with_label("Open");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(menu_pressed), NULL);

	menu_item = gtk_menu_item_new_with_label("Exit");
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(menu_pressed), NULL);
	

	menu_item = gtk_menu_item_new_with_label("About");
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(menu_pressed), NULL);

	menu_item = gtk_menu_item_new_with_label("Help");
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(menu_pressed), NULL);
	


	gtk_box_pack_start(GTK_BOX(vbox), menu_bar, 0, 0, 0);	
	button = gtk_button_new_with_label("click me");

	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

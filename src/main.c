#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "gamedata.h"

struct arginfo {
	int argc;
	char **argv;
};

int printBINheader(const char *path) {
	FILE *fpk;
	fpk = fopen(path, "rb");
	if(fpk == NULL) {
		printf("couldn't open %s\n", path);
		return -1;
	}
	struct bin_index index;
	fseek(fpk, 8, SEEK_SET);
	fread(&index.entries, sizeof(uint32_t), 1, fpk);
	fseek(fpk, 40, SEEK_SET);
	fread(&index.start, sizeof(uint32_t), 1, fpk);
	close(fpk);
	return printf(
		"%s:\t\tentries: %u\t\tstart: %u\n",
		path, index.entries, index.start
	);
}

int printFPKheader(FILE *fpk) {
	struct fpk_header header;
	fseek(fpk, 0, SEEK_SET);
	fread(&header, sizeof(struct fpk_header), 1, fpk);
	return printf(
		"flag: %u\nlzs_n: %u\nlzs_p: %u\nsize: %u\n",
		header.flag, header.lzs_n, header.lzs_p, header.size
	);
}

static void print_hello(GtkWidget *widget, gpointer data) {
	g_print("Hello world\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *text;
	GListModel *list;
	//struct arginfo info = *((struct arginfo*) user_data);

	//printf("%d %s\n", info.argc, info.argv[0]);
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 480, 640);

	layout = gtk_list_box_new();
	text = gtk_label_new("meow");
	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

	gtk_list_box_append(layout, button);
	gtk_list_box_append(layout, text);

//	gtk_window_set_child(GTK_WINDOW(window), text);
//	gtk_window_set_child(GTK_WINDOW(window), button);

	gtk_window_set_child(GTK_WINDOW(window), layout);
	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
	GtkApplication *app;
	int status;
	struct arginfo info = { argc, argv };
	gpointer infop = &info;
	//const char path[] = "./disc/faceuc.bin";
	int binc = 6;
	const char *paths[] = {
		"./disc/faceuc.bin",
		"./disc/image.bin",
		"./disc/movie0uc.bin",
		"./disc/movie1uc.bin",
		"./disc/sndimguc.bin",
		"./disc/voiceuc.bin"
	};
	for(int i = 0; i < binc; i++){
		printBINheader(paths[i]);
	}
	// G_APPLICATION_DEFAULT_FLAGS is new so possibly system gtk4 is out of date
	//app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	app = gtk_application_new("com.github.aj-m.drakenbuild", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), infop);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}

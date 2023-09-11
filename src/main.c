#include <gtk/gtk.h>
#include <stdio.h>
#include "gamedata.h"

/*
struct BINheader {
	char magic[4];    // fpk (unless it's a movie*uc.bin)
	uint32_t entries; // number of files in archive
};

struct FPKheader {
	uint32_t flag;     // null
	uint32_t lzs_n;    // count of all files in archive
	uint32_t lzs_p;    // size of archive header
	uint32_t size;     // size of the whole file
};

struct FPKentry {
	char name[20];     // entry name
	uint32_t data_p;   // offset to entry
	uint32_t dst_size; // compressed entry size
	uint32_t src_size; // uncompressed entry size
};

struct FPKarchive {
	struct FPKheader header;
	struct FPKentry  entries[0];
};
*/

int printBINheader(FILE *fpk) {
	struct bin_header header;
	fseek(fpk, 0, SEEK_SET);
	fread(&header, sizeof(struct bin_header), 1, fpk);
	return printf(
		"magic: %s\nentries: %u\n",
		header.magic, header.entries_n
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

//int listbinfiles(char[] binpath, char[] filelist /*out*/) {
//	return -1;
//}

static void print_hello(GtkWidget *widget, gpointer data) {
	g_print("Hello world\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *button;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
	gtk_window_set_child(GTK_WINDOW(window), button);

	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
	GtkApplication *app;
	int status;
	//const char path[] = "./disc/faceuc.bin";
	const char path[] = "./disc/voiceuc.bin";
	FILE *fpkarchive;

	fpkarchive = fopen(&path, "rb");
	if(fpkarchive != NULL) {
		printBINheader(fpkarchive);
		//printFPKheader(fpkarchive);
		close(fpkarchive);
	} else {
		printf("couldn't open %s\n", path);
	}
	// G_APPLICATION_DEFAULT_FLAGS is new so possibly system gtk4 is out of date
	//app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	app = gtk_application_new("com.github.aj-m.drakenbuild", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}

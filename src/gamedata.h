#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdint.h>

struct bin_header {
	char magic[4];       // usually will be "fpk\0" because that's not confusing
	uint32_t entries_n;  // number of files in archive (maybe not? possibly have wrong offset)
};

struct bin_entry {
	uint32_t placeholder;
};

struct bin_file {
	struct bin_header header;
	struct bin_entry  entries[0]; // it's a pointer to an array but this should simplify semantics
};

struct fpk_header {
	uint32_t flag;
	uint32_t lzs_n;    // file count
	uint32_t lzs_p;    // size of header (data offset?)
	uint32_t size;     // file size
};

struct fpk_entry {
	char name[20];     // entry name
	uint32_t data_p;   // offset to entry
	uint32_t dst_size; // compressed size
	uint32_t src_size; // uncompressed size
};

struct fpk_file {
	struct fpk_header header;
	struct fpk_entry  entries[0];
};

#endif

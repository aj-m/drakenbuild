#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdint.h>

struct bin_index {
	uint32_t entries;  // number of files in archive
	uint32_t start;    // byte offset where file data starts
};

struct bin_entry {
	uint32_t offset;     // byte offset where entry data starts
	uint32_t size;       // number of bytes in entry
};

struct bin_file {
	struct bin_index header;
	struct bin_entry **entries; // it's a pointer to an array
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

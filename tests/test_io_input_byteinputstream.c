/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdlib.h>
#include "test_io_input_byteinputstream.h"
#include "test_unit.h"
#include "../src/io/input/byte_input_stream.h"

const char *test_io_byis_create_free() {
	byte_input_stream *byis = byis_create(NULL, false);
	assertNotNull(byis);
	assertNotNull(byis->buffer);
	byis_free(byis);
	return 0;
}

const char *test_io_byis_read() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	for (size_t i = 0; i < INPUT_BUFFER_SIZE * 2; ++i) {
		fprintf(memfile, "%c", (byte) (i % 256));
	}
	
	byte_input_stream *byis = byis_create(memfile, true);
	
	for (size_t i = 0; i < INPUT_BUFFER_SIZE * 2; ++i) {
		assertEquals(byis_read(byis), (byte) (i % 256));
	}
	
	byis_free(byis);
	
	fclose(memfile);
	
	free(buf);
	
	return 0;
}

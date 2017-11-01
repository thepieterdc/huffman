/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_byteinputstream.h"
#include "test_unit.h"
#include "../src/io/input/byte_input_stream.h"

static const char *test_read_count(byte_input_stream *byis, size_t amount) {
	for (size_t i = 0; i < amount; ++i) {
		assertEquals(byis_read(byis), (byte) (i % 256));
	}
	return 0;
}

const char *test_io_byis_create_free() {
	byte_input_stream *byis = byis_create(stdin, false);
	assertNotNull(byis);
	assertNotNull(byis->buffer);
	byis_free(byis);
	return 0;
}

const char *test_io_byis_feed_byte_read() {
	byte_input_stream *byis = byis_create(NULL, false);
	
	for (size_t i = 0; i < INPUT_BUFFER_SIZE * 2; ++i) {
		byis_feed_byte(byis, (byte) (i % 256));
	}
	
	assertEquals(test_read_count(byis, INPUT_BUFFER_SIZE), 0);
	
	byis_free(byis);
	
	return 0;
}

const char *test_io_byis_feed_stream_read() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	byte_input_stream *byis = byis_create(memfile, true);
	
	for (size_t i = 0; i < INPUT_BUFFER_SIZE * 2; ++i) {
		fprintf(memfile, "%c", (byte) (i % 256));
	}
	
	assertEquals(test_read_count(byis, INPUT_BUFFER_SIZE * 2), 0);
	
	byis_free(byis);
	
	free(buf);
	
	return 0;
}

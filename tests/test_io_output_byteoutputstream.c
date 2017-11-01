/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_byteoutputstream.h"
#include "test_unit.h"
#include "../src/io/output/byte_output_stream.h"

const char *test_io_byos_create_free() {
	byte_output_stream *bos = byos_create(NULL);
	assertNotNull(bos);
	byos_free(bos);
	return 0;
}

const char *test_io_byos_feed_flush() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	byte_output_stream *byos = byos_create(memfile);
	
	assertEquals(byos->buffer_size, 0);
	
	for (size_t i = 0; i < 256; ++i) {
		byos_feed(byos, (byte) i);
	}
	
	assertEquals(byos->buffer_size, 256);
	
	byos_flush(byos);
	
	assertEquals(byos->buffer_size, 0);
	
	for (size_t i = 0; i < 256; ++i) {
		assertEquals((byte) getc(memfile), (byte) i);
	}
	
	byos_free(byos);
	
	free(buf);
	
	return 0;
}
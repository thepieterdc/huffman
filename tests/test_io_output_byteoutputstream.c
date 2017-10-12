/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_byteoutputstream.h"
#include "test_unit.h"
#include "../src/io/output/byte_output_stream.h"

char *test_io_byos_create_free() {
	byte_output_stream *bos = byos_create(NULL);
	assertThat(bos != NULL);
	assertThat(bos->stream != NULL);
	byos_free(bos);
	return 0;
}

char *test_io_byos_feed_flush_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);

	byte_output_stream *byos = byos_create(memfile);

	assertThat(byos_count(byos) == 0);

	for (size_t i = 0; i < 256; ++i) {
		byos_feed(byos, (byte) i);
	}

	assertThat(byos_count(byos) == 256);

	byos_flush(byos);

	assertThat(byos_count(byos) == 0);

	for (size_t i = 0; i < 256; ++i) {
		assertThat((byte) getc(memfile) == (byte) i);
	}

	byos_free(byos);
	
	return 0;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_byteinputstream.h"
#include "test_unit.h"
#include "../src/io/input/byte_input_stream.h"

static char *test_read_count(byte_input_stream *bis) {
	assertThat(byis_count(bis) == 9);
	
	for (size_t i = 1; i <= 9; ++i) {
		assertThat(byis_read(bis) == (byte) i);
	}
	assertThat(byis_count(bis) == 0);
	
	return 0;
}

char *test_io_byis_create_free() {
	byte_input_stream *bis = byis_create(stdin);
	assertThat(bis != NULL);
	assertThat(bis->stream != NULL);
	byis_free(bis);
	return 0;
}

char *test_io_byis_consume_read_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	byte_input_stream *bis = byis_create(memfile);
	
	assertThat(byis_count(bis) == 0);
	
	for (size_t i = 1; i <= 9; ++i) {
		fprintf(memfile, "%c", (byte) i);
	}
	
	byis_consume(bis);
	
	assertThat(test_read_count(bis) == 0);
	
	byis_free(bis);
	
	free(buf);
	
	return 0;
}

char *test_io_byis_feed_read_count() {
	byte_input_stream *bis = byis_create(stdin);
	
	assertThat(byis_count(bis) == 0);
	
	for (size_t i = 1; i <= 9; ++i) {
		byis_feed(bis, (byte) i);
	}
	
	assertThat(test_read_count(bis) == 0);
	
	byis_free(bis);
	
	return 0;
}
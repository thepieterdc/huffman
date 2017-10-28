/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_outputstream.h"
#include "test_unit.h"
#include "../src/io/output/output_stream.h"

char *test_io_os_create_free() {
	output_stream *os = os_create(NULL);
	assertThat(os != NULL);
	os_free(os);
	return 0;
}

char *test_io_os_feed_read_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	output_stream *os = os_create(memfile);
	
	assertThat(os->buffer_size == 0);
	
	os_feed(os, 0b100);
	os_feed(os, 0b101);
	
	assertThat(os->buffer_size == 2);
	
	os_flush(os);
	
	assertThat(getc(memfile) == 0b100);
	assertThat(getc(memfile) == 0b101);
	
	assertThat(os->buffer_size == 0);
	
	os_free(os);
	
	free(buf);
	
	return 0;
}
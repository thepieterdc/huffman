/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_outputstream.h"
#include "test_unit.h"
#include "../src/io/output/output_stream.h"
#include "../src/datatypes/string.h"
#include "../src/util/string.h"

char *test_io_os_create_free() {
	output_stream *os = os_create(NULL);
	assertThat(os != NULL);
	assertThat(os->buffer != NULL);
	os_free(os);
	return 0;
}

char *test_io_os_feed_read_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	output_stream *os = os_create(memfile);
	
	assertThat(os_count(os) == 0);
	
	os_feed(os, (void *) 5);
	os_feed(os, (void *) 6);
	
	assertThat(os_count(os) == 2);
	
	os_flush(os);
	
	assertThat(getc(memfile) == 5);
	assertThat(getc(memfile) == 6);
	
	assertThat(os_count(os) == 0);
	
	os_free(os);
	
	free(buf);
	
	return 0;
}
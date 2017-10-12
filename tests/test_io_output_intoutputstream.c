/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_intoutputstream.h"
#include "test_unit.h"
#include "../src/io/output/int_output_stream.h"

char *test_io_ios_create_free() {
	int_output_stream *ios = ios_create(NULL);
	assertThat(ios != NULL);
	assertThat(ios->stream != NULL);
	ios_free(ios);
	return 0;
}

char *test_io_ios_feed_flush_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	int_output_stream *ios = ios_create(memfile);
	
	assertThat(ios_count(ios) == 0);
	
	ios_feed(ios, 5);
	ios_feed(ios, 6);
	
	assertThat(ios_count(ios) == 2);
	
	ios_flush(ios);
	
	assertThat(getc(memfile) == 5);
	assertThat(getc(memfile) == 6);
	
	assertThat(ios_count(ios) == 0);
	
	ios_free(ios);
	
	return 0;
}
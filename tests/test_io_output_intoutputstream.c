/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_intoutputstream.h"
#include "test_unit.h"
#include "../src/io/output/int_output_stream.h"
#include "../src/util/string.h"

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

	for (size_t i = 0; i < 10; ++i) {
		ios_feed(ios, (int) i);
	}

	assertThat(ios_count(ios) == 10);

	ios_flush(ios);

	assertThat(ios_count(ios) == 0);

	for (size_t i = 0; i < 10; ++i) {
		assertThat(char_to_int((size_t) getc(memfile)) == (int) i);
	}

	ios_free(ios);
	
	free(buf);
	
	return 0;
}
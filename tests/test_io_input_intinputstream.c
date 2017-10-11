/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_intinputstream.h"
#include "test_unit.h"
#include "../src/io/input/int_input_stream.h"

static char *test_read_count(int_input_stream *iis) {
	assertThat(iis_count(iis) == 9);
	
	for (size_t i = 1; i <= 9; ++i) {
		assertThat(iis_read(iis) == (int) i);
	}
	assertThat(iis_count(iis) == 0);
	
	return 0;
}

char *test_io_iis_create_free() {
	int_input_stream *iis = iis_create(stdin);
	assertThat(iis != NULL);
	assertThat(iis->stream != NULL);
	iis_free(iis);
	return 0;
}

char *test_io_iis_consume_read_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	int_input_stream *iis = iis_create(memfile);
	
	assertThat(iis_count(iis) == 0);
	
	fprintf(memfile, "%d", 123456789);
	iis_consume(iis);
	
	assertThat(test_read_count(iis) == 0);
	
	iis_free(iis);
	free(buf);
	
	return 0;
}

char *test_io_iis_feed_read_count() {
	int_input_stream *iis = iis_create(stdin);
	
	assertThat(iis_count(iis) == 0);
	
	for (size_t i = 1; i <= 9; ++i) {
		iis_feed(iis, (int) i);
	}
	
	assertThat(test_read_count(iis) == 0);
	
	iis_free(iis);
	
	return 0;
}
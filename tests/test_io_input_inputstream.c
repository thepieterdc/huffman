/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_inputstream.h"
#include "test_unit.h"
#include "../src/io/input/input_stream.h"
#include "../src/datatypes/string.h"
#include "../src/util/string.h"

char *test_io_is_create_free() {
	input_stream *is = is_create();
	assertThat(is != NULL);
	assertThat(is->buffer != NULL);
	is_free(is);
	return 0;
}

char *test_io_is_feed_read_count() {
	input_stream *is = is_create();
	
	is_feed(is, "5");
	is_feed(is, "6");
	
	assertThat(is_count(is) == 2);
	assertThat(str_equals(is_read(is), "5"));
	assertThat(str_equals(is_read(is), "6"));
	
	is_free(is);
	
	return 0;
}
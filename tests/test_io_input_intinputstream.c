/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_intinputstream.h"
#include "test_unit.h"
#include "../src/io/input/int_input_stream.h"

char *test_io_iis_create_free() {
	int_input_stream *iis = iis_create(stdin);
	assertThat(iis != NULL);
	assertThat(iis->stream != NULL);
	iis_free(iis);
	return 0;
}
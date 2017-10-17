/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_bitinputstream.h"
#include "test_unit.h"
#include "../src/io/input/bit_input_stream.h"

char *test_io_bis_create_free() {
	bit_input_stream *bis = bis_create(NULL);
	assertThat(bis != NULL);
	assertThat(bis->bytestream != NULL);
	bis_free(bis);
	return 0;
}

char *test_io_bis_read_bit_count_clear_buffer() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	fprintf(memfile, "%c", 0b01010101);
	fprintf(memfile, "%c", 0b10101010);
	
	bit_input_stream *bis = bis_create(memfile);
	
	assertThat(bis_count(bis) == 16);
	
	for (size_t i = 0; i < 8; ++i) {
		assertThat(bis_read_bit(bis) % 2 == i % 2);
	}
	
	assertThat(bis_count(bis) == 8);
	
	for (size_t i = 0; i < 6; ++i) {
		assertThat(bis_read_bit(bis) % 2 != i % 2);
	}
	
	assertThat(bis_count(bis) == 2);
	
	bis_clear_buffer(bis);
	
	assertThat(bis_count(bis) == 0);
	
	bis_free(bis);
	
	free(buf);
	
	return 0;
}

char *test_io_bis_read_byte_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	fprintf(memfile, "%c", (byte) 70);
	fprintf(memfile, "%c", (byte) 71);
	
	bit_input_stream *bis = bis_create(memfile);
	
	assertThat(bis_count(bis) == 16);
	
	for (size_t i = 70; i < 72; ++i) {
		assertThat(bis_read_byte(bis) == (byte) i);
	}
	assertThat(bis_count(bis) == 0);
	
	bis_free(bis);
	
	free(buf);
	
	return 0;
}
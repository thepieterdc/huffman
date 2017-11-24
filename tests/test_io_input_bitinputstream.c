/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_bitinputstream.h"
#include "test_unit.h"
#include "../src/io/input/bit_input_stream.h"

const char *test_io_bis_create_free() {
	bit_input_stream *bis = bis_create(NULL, false);
	assertNotNull(bis);
	assertNotNull(bis->stream);
	bis_free(bis);
	return 0;
}

const char *test_io_bis_read_bit() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	fprintf(memfile, "%c", 0b01010101);
	fprintf(memfile, "%c", 0b10101010);
	
	bit_input_stream *bis = bis_create(memfile, false);
	
	for (size_t i = 0; i < 8; ++i) {
		assertEquals(bis_read_bit(bis) % 2, i % 2);
	}
	
	for (size_t i = 0; i < 6; ++i) {
		assertNotEquals(bis_read_bit(bis) % 2, i % 2);
	}
	
	bis_free(bis);
	
	fclose(memfile);
	
	free(buf);
	
	return 0;
}

const char *test_io_bis_read_byte() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	for (size_t i = 0; i < INPUT_BUFFER_SIZE * 2; ++i) {
		fprintf(memfile, "%c", (byte) (i % 256));
	}
	
	bit_input_stream *bis = bis_create(memfile, true);
	
	for (size_t i = 0; i < INPUT_BUFFER_SIZE * 2; ++i) {
		assertEquals(bis_read_byte(bis), (byte) (i % 256));
	}
	
	bis_free(bis);
	
	fclose(memfile);
	
	free(buf);
	
	return 0;
}
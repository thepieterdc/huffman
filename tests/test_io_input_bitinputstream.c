/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_input_bitinputstream.h"
#include "test_unit.h"
#include "../src/io/input/bit_input_stream.h"

static char *test_read_bit_count(bit_input_stream *bis) {
	assertThat(bis_count(bis) == 16);
	
	for (size_t i = 0; i < 8; ++i) {
		assertThat(bis_read_bit(bis) % 2 == i % 2);
	}
	
	for (size_t i = 0; i < 8; ++i) {
		assertThat(bis_read_bit(bis) % 2 != i % 2);
	}
	
	assertThat(bis_count(bis) == 0);
	
	return 0;
}

char *test_io_bis_create_free() {
	bit_input_stream *bis = bis_create(stdin);
	assertThat(bis != NULL);
	assertThat(bis->bytestream != NULL);
	bis_free(bis);
	return 0;
}

char *test_io_bis_consume_read_bit_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);

	bit_input_stream *bis = bis_create(memfile);

	assertThat(bis_count(bis) == 0);

	fprintf(memfile, "%d", 0b01010101);
	fprintf(memfile, "%d", 0b10101010);

	bis_consume(bis);

//	assertThat(test_read_bit_count(bis) == 0);
	assertThat(bis_count(bis) == 16);
	
	for (size_t i = 0; i < 8; ++i) {
		assertThat(bis_read_bit(bis) % 2 == i % 2);
	}
	
	for (size_t i = 0; i < 8; ++i) {
		assertThat(bis_read_bit(bis) % 2 != i % 2);
	}
	
	assertThat(bis_count(bis) == 0);
	
	bis_free(bis);
	free(buf);
	
	return 0;
}

char *test_io_bis_feed_bit_read_bit_count() {
//	byte_input_stream *bis = byis_create(stdin);
//
//	assertThat(byis_count(bis) == 0);
//
//	for (size_t i = 1; i <= 9; ++i) {
//		byis_feed(bis, (byte) i);
//	}
//
//	assertThat(test_read_count(bis) == 0);
//
//	byis_free(bis);
	
	return 1;
}

char *test_io_bis_feed_byte_read_byte_count() {
//	byte_input_stream *bis = byis_create(stdin);
//
//	assertThat(byis_count(bis) == 0);
//
//	for (size_t i = 1; i <= 9; ++i) {
//		byis_feed(bis, (byte) i);
//	}
//
//	assertThat(test_read_count(bis) == 0);
//
//	byis_free(bis);
	
	return 1;
}
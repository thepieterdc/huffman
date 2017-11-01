/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_io_output_bitoutputstream.h"
#include "test_unit.h"
#include "../src/io/output/bit_output_stream.h"

const char *test_io_bos_create_free() {
	bit_output_stream *bos = bos_create(NULL);
	assertNotNull(bos);
	assertNotNull(bos->stream);
	bos_free(bos);
	return 0;
}

const char *test_io_bos_feed_bit_flush_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	bit_output_stream *bos = bos_create(memfile);
	
	assertEquals(bos_count(bos), 0);
	
	for (size_t i = 0; i < 8; ++i) {
		bos_feed_bit(bos, (bit) (i % 2) != 0);
	}
	
	assertEquals(bos_count(bos), 8);
	
	for (size_t i = 0; i < 8; ++i) {
		bos_feed_bit(bos, (bit) (i % 2) == 0);
	}
	
	assertEquals(bos_count(bos), 16);
	
	bos_flush(bos);
	
	assertEquals(bos_count(bos), 0);
	
	assertEquals((byte) getc(memfile), (byte) 0b01010101);
	assertEquals((byte) getc(memfile), (byte) 0b10101010);
	
	bos_free(bos);
	
	free(buf);
	
	return 0;
}

const char *test_io_bos_feed_bit_pad_flush_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	bit_output_stream *bos = bos_create(memfile);
	
	assertEquals(bos_count(bos), 0);
	
	for (size_t i = 0; i < 4; ++i) {
		bos_feed_bit(bos, (bit) (i % 2) != 0);
	}
	
	assertEquals(bos_count(bos), 4);
	
	assertEquals(bos_pad(bos), 4);
	
	assertEquals(bos_count(bos), 8);
	
	bos_flush(bos);
	
	assertEquals(bos_count(bos), 0);
	
	assertEquals((byte) getc(memfile), (byte) 0b01010000);
	
	bos_free(bos);
	
	free(buf);
	
	return 0;
}

const char *test_io_bos_feed_byte_flush_count() {
	char *buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	bit_output_stream *bos = bos_create(memfile);
	
	assertEquals(bos_count(bos), 0);
	
	bos_feed_byte(bos, (byte) 0b01010101);
	bos_feed_byte(bos, (byte) 0b10101010);
	
	assertEquals(bos_count(bos), 16);
	
	bos_flush(bos);
	
	assertEquals(bos_count(bos), 0);
	
	assertEquals((byte) getc(memfile), 0b01010101);
	assertEquals((byte) getc(memfile), 0b10101010);
	
	bos_free(bos);
	
	free(buf);
	
	return 0;
}
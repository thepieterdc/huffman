/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"

#include "test_io_bitstream.h"
#include "../src/io/bitstream.h"

char *test_bs_create_free() {
	bitstream *bs = bs_create();
	assertThat(bs != NULL);
	bs_free(bs);
	return 0;
}

char *test_bs_add_bit() {
	bitstream *bs = bs_create();
	assertThat(bs != NULL);
	
	bs_add_bit(bs, false);
	bs_add_bit(bs, true);
	bs_add_bit(bs, false);
	bs_add_bit(bs, true);
	bs_add_bit(bs, false);
	bs_add_bit(bs, true);
	bs_add_bit(bs, false);
	
	assertThat(bs->current_byte == 42);
	
	bs_free(bs);
	
	return 0;
}

char *test_bs_add_byte() {
	bitstream *bs = bs_create();
	assertThat(bs != NULL);
	
	bs_add_byte(bs, 240);
	
	byte b = (byte) queue_peek(bs->buffer);
	assertThat(b == 240);
	
	bs_free(bs);
	
	return 0;
}
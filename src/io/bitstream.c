/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bitstream.h"
#include "../util/errors.h"
#include "../util/logging.h"

void bs_add_bit(bitstream *bs, bool bit) {
	bs->current_byte <<= 1;
	bs->current_byte += bit;
	bs->current_byte_cursor++;
	
	if (bs->current_byte_cursor == 8) {
		bs_add_byte(bs, bs->current_byte);
		bs->current_byte = 0;
		bs->current_byte_cursor = 0;
	}
}

void bs_add_byte(bitstream *bs, byte b) {
	queue_push(bs->buffer, (void *) b);
}

bitstream *bs_create() {
	bitstream *ret = (bitstream *) malloc(sizeof(bitstream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->buffer = queue_create();
		ret->current_byte = 0;
		ret->current_byte_cursor = 0;
	}
	return ret;
}

void bs_free(bitstream *bs) {
	queue_free(bs->buffer);
	free(bs);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bitstream.h"
#include "logging.h"
#include "errors.h"

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
	free(bs->buffer);
	free(bs);
}
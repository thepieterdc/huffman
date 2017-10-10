/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#define BS_BUFFER_SIZE 256

#include "bitstream.h"

bitprinter *bp_create(FILE *channel) {
	bitprinter *ret = malloc(sizeof(bitprinter));
	if (ret == NULL) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->buffer = 0;
		ret->cursor = 0;
		ret->channel = channel;
	}
	return ret;
}
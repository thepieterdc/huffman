/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bitprinter.h"
#include "errors.h"
#include "logging.h"

bitprinter *bitprinter_create(FILE *channel) {
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

void bitprinter_flush(bitprinter *bp) {
	if (bp->cursor != 0) {
		if (bp->cursor != 8) {
			size_t padding = 8 - bp->cursor;
			bp->buffer <<= padding;
		}
		printf("%c", bp->buffer);
		bp->buffer = 0;
		bp->cursor = 0;
	}
}

void bitprinter_free(bitprinter *bp, bool flush) {
	if (flush) {
		bitprinter_flush(bp);
	}
	free(bp);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_input_stream.h"
#include "../../util/errors.h"
#include "../../util/logging.h"
#include "../../util/binary.h"


void bis_consume(bit_input_stream *bis) {
	byis_consume(bis->bytestream);
}

size_t bis_count(bit_input_stream *bis) {
	size_t bufsize = bis->empty ? 0 : (8 - bis->current_cursor);
	return byis_count(bis->bytestream) * 8 + bufsize;
}

bit_input_stream *bis_create(FILE *channel) {
	bit_input_stream *ret = (bit_input_stream *) malloc(sizeof(bit_input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->bytestream = byis_create(channel);
		ret->current_byte = 0;
		ret->current_cursor = 0;
		ret->empty = true;
	}
	return ret;
}

void bis_free(bit_input_stream *bis) {
	byis_free(bis->bytestream);
	free(bis);
}

bit bis_read_bit(bit_input_stream *bis) {
	printf("READ\n");
	if (bis->current_cursor == 7) {
		printf("EMPTY\n");
		bis->empty = true;
	}
	
	if (bis->empty) {
		bis->current_byte = byis_read(bis->bytestream);
		bis->current_cursor = 0;
		bis->empty = false;
	}
	
	bit ret = (bit) (bis->current_byte & (1 << 7));
	
	bis->current_byte <<= 1;
	
	bis->current_cursor++;
	
	return ret;
}

byte bis_read_byte(bit_input_stream *bis) {
	return 1;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_input_stream.h"
#include "../../util/binary.h"
#include "../../util/memory.h"

void bis_clear_buffer(bit_input_stream *bis) {
	bis->current_byte = 0;
	bis->current_cursor = 8;
	bis->empty = true;
}

size_t bis_count(bit_input_stream *bis) {
	size_t buffer = bis->empty ? 0 : (8 - bis->current_cursor);
	return byis_count(bis->bytestream) * 8 + buffer;
}

bit_input_stream *bis_create(FILE *channel) {
	bit_input_stream *ret = (bit_input_stream *) mallocate(sizeof(bit_input_stream));
	ret->bytestream = byis_create(channel);
	ret->current_byte = 0;
	ret->current_cursor = 0;
	ret->empty = true;
	
	if (channel) {
		byis_consume(ret->bytestream);
	}
	return ret;
}

bool bis_empty(bit_input_stream *bis) {
	return bis_count(bis) == 0;
}

void bis_free(bit_input_stream *bis) {
	byis_free(bis->bytestream);
	free(bis);
}

bit bis_read_bit(bit_input_stream *bis) {
	if (bis->current_cursor == 8) {
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
	if (!bis->empty) {
		byte ret = bis->current_byte >> bis->current_cursor;
		bis->current_byte = 0;
		bis->current_cursor = 0;
		bis->empty = true;
		return ret;
	}
	return byis_read(bis->bytestream);
}

/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_input_stream.h"
#include "../../util/binary.h"
#include "../../util/memory.h"
#include "byte_input_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"

/** Mappings. */
static byte bis_read_bit_map[BITS_IN_BYTE] = {
		0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1
};

void bis_clear_current_byte(bit_input_stream *bis) {
	bis->current_byte = 0;
	bis->current_cursor = BITS_IN_BYTE;
}

bit_input_stream *bis_create(FILE *channel, bool retain) {
	bit_input_stream *ret = (bit_input_stream *) callocate(1, sizeof(bit_input_stream));
	ret->current_cursor = BITS_IN_BYTE;
	ret->stream = byis_create(channel, retain);
	return ret;
}

void bis_flush(bit_input_stream *bis) {
	bis->current_byte = 0;
	bis->current_cursor = BITS_IN_BYTE;
	bis->stream->buffer_size = 0;
}

void bis_free(bit_input_stream *bis) {
	byis_free(bis->stream);
	free(bis);
}

/* 462,383,138 I ; 34.08% */
bit bis_read_bit(bit_input_stream *bis) {
	if (bis->current_cursor == BITS_IN_BYTE) {
		bis->current_byte = byis_read(bis->stream);
		bis->current_cursor = 0;
	}
	
	return (bit) (bis->current_byte & bis_read_bit_map[bis->current_cursor++]);
}

byte bis_read_byte(bit_input_stream *bis) {
	if (bis->current_cursor != BITS_IN_BYTE) {
		byte ret = 0;
		for (size_t i = 0; i < BITS_IN_BYTE; ++i) {
			ret <<= 1;
			ret |= bis_read_bit(bis);
		}
		return ret;
	}
	return byis_read(bis->stream);
}

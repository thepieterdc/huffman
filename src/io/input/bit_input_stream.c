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

void bis_clear_current_byte(bit_input_stream *bis) {
	bis->current_byte = 0;
	bis->current_cursor = 8;
}

bit_input_stream *bis_create(FILE *channel, bool retain) {
	bit_input_stream *ret = (bit_input_stream *) callocate(1, sizeof(bit_input_stream));
	ret->current_cursor = 8;
	ret->stream = byis_create(channel, retain);
	return ret;
}

void bis_free(bit_input_stream *bis) {
	byis_free(bis->stream);
	free(bis);
}

bit bis_read_bit(bit_input_stream *bis) {
	if (bis->current_cursor == 8) {
		bis->current_byte = byis_read(bis->stream);
		bis->current_cursor = 0;
		if (bis->stream->end) {
			error(ERROR_END_OF_INPUT);
		}
	}
	
	bit ret = (bit) (bis->current_byte & (1 << 7));
	
	bis->current_byte <<= 1;
	
	bis->current_cursor++;
	
	return ret;
}

byte bis_read_byte(bit_input_stream *bis) {
	if (bis->current_cursor != 8) {
		byte ret = bis->current_byte >> bis->current_cursor;
		bis->current_byte = 0;
		bis->current_cursor = 8;
		return ret;
	}
	return byis_read(bis->stream);
}

/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_input_stream.h"
#include "../../util/errors.h"
#include "../../util/logging.h"


void bis_consume(bit_input_stream *bis) {
	byis_consume(bis->bytestream);
}

size_t bis_count(bit_input_stream *bis) {
	return byis_count(bis->bytestream) * 8 - bis->current_cursor;
}

bit_input_stream *bis_create(FILE *channel) {
	bit_input_stream *ret = (bit_input_stream *) malloc(sizeof(bit_input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->bytestream = byis_create(channel);
		ret->current_cursor = 0;
	}
	return ret;
}

//void byis_feed(byte_input_stream *bis, byte b) {
//	is_feed(bis->stream, (void *) b);
//}

void bis_free(bit_input_stream *bis) {
	byis_free(bis->bytestream);
	free(bis);
}

bit bis_read_bit(bit_input_stream *bis) {
	if (bis->current_cursor >= 7) {
		bis->current_byte = byis_read(bis->bytestream);
		bis->current_cursor = 0;
	}
	bit ret = (bit) (bis->current_byte & (1 << 7));
	bis->current_byte <<= 1;
	bis->current_cursor++;
	return ret;
}

byte bis_read_byte(bit_input_stream *bis) {
	byte ret;
	if (bis->current_cursor >= 7) {
		ret = byis_read(bis->bytestream);
	} else {
		ret = bis->current_byte;
		bis->current_byte = 0;
		bis->current_cursor = 8;
	}
}

//byte byis_read(byte_input_stream *bis) {
//	return (byte) is_read(bis->stream);
//}
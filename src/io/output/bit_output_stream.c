/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_output_stream.h"
#include "../../util/errors.h"
#include "../../util/logging.h"
#include "../../util/binary.h"
#include "byte_output_stream.h"
#include "output_stream.h"

static void add_buffer_to_stream(bit_output_stream *bos) {
	byos_feed(bos->stream, bos->current_byte);
	bos->current_byte = 0;
	bos->current_cursor = 0;
}

size_t bos_count(bit_output_stream *bos) {
	return byos_count(bos->stream) * 8 + bos->current_cursor;
}

bit_output_stream *bos_create(FILE *channel) {
	bit_output_stream *ret = (bit_output_stream *) malloc(sizeof(bit_output_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->stream = byos_create(channel);
		ret->current_byte = 0;
		ret->current_cursor = 0;
	}
	return ret;
}

void bos_feed_bit(bit_output_stream *bos, bit b) {
	if (bos->current_cursor == 8) {
		add_buffer_to_stream(bos);
	}
	bos->current_byte <<= 1;
	bos->current_byte |= b;
	bos->current_cursor++;
}

void bos_feed_byte(bit_output_stream *bos, byte b) {
	if (bos->current_cursor == 0) {
		byos_feed(bos->stream, b);
	} else {
		for (size_t i = 0; i < 8; ++i) {
			bos_feed_bit(bos, (bit) (b & (1 << (7 - i))));
		}
	}
}

void bos_flush(bit_output_stream *bos) {
	add_buffer_to_stream(bos);
	byos_flush(bos->stream);
}

void bos_free(bit_output_stream *bos) {
	byos_free(bos->stream);
	free(bos);
}

size_t bos_pad(bit_output_stream *bos) {
	size_t padding = 8 - bos->current_cursor;
	bos->current_byte <<= padding;
	
	add_buffer_to_stream(bos);
	
	return padding;
}
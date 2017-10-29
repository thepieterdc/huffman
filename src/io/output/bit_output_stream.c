/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <math.h>
#include "bit_output_stream.h"
#include "../../util/binary.h"
#include "byte_output_stream.h"
#include "byte_output_stream.h"
#include "../../util/memory.h"

static void add_buffer_to_stream(bit_output_stream *bos) {
	bos->current_byte <<= (8 - bos->current_cursor);
	byos_feed(bos->stream, bos->current_byte);
	bos->current_byte = 0;
	bos->current_cursor = 0;
}

size_t bos_count(bit_output_stream *bos) {
	return bos->stream->buffer_size * 8 + bos->current_cursor;
}

bit_output_stream *bos_create(FILE *channel) {
	bit_output_stream *ret = (bit_output_stream *) mallocate(sizeof(bit_output_stream));
	ret->stream = byos_create(channel);
	ret->current_byte = 0;
	ret->current_cursor = 0;
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
			bos_feed_bit(bos, (bit) (b & (1 << (7 - i))) != 0);
		}
	}
}

void bos_feed_huffmancode(bit_output_stream *bos, huffman_code *hc) {
	for (size_t pad = 0; pad < hc->padding; ++pad) {
		bos_feed_bit(bos, 0);
	}
	
	if (hc->code == 0) return;
	
	uint_fast64_t mask = ((uint_fast64_t) 1) << 63;
	while ((mask > 0) && ((hc->code & mask) == 0)) mask >>= 1;
	
	do {
		bos_feed_bit(bos, (hc->code & mask) != 0);
		mask >>= 1;
	} while (mask > 0);
}

void bos_flush(bit_output_stream *bos) {
	if (bos->current_cursor != 0) {
		add_buffer_to_stream(bos);
	}
	byos_flush(bos->stream);
}

void bos_free(bit_output_stream *bos) {
	byos_free(bos->stream);
	free(bos);
}

size_t bos_pad(bit_output_stream *bos) {
	size_t padding = 8 - bos->current_cursor;
	bos->current_byte <<= padding;
	bos->current_cursor = 8;
	add_buffer_to_stream(bos);
	
	return padding;
}
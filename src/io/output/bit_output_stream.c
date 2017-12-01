/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdlib.h>
#include "bit_output_stream.h"
#include "../../util/memory.h"

bit_output_stream *bos_create(FILE *channel) {
	bit_output_stream *ret = (bit_output_stream *) mallocate(sizeof(bit_output_stream));
	ret->channel = channel;
	ret->current_buffer = 0;
	ret->current_cursor = BIT_OUTPUT_STREAM_SIZE_BITS;
	if (channel) {
		flockfile(channel);
#ifdef IS_DEBUG
#ifndef IS_TEST
		setvbuf(channel, NULL, _IONBF, OUTPUT_BUFFER_SIZE);
#endif
#else
		setvbuf(channel, NULL, _IOFBF, OUTPUT_BUFFER_SIZE);
#endif
	}
	return ret;
}

void bos_feed_bits(bit_output_stream *bos, uint_fast64_t bits, uint_fast8_t left) {
	register size_t cursor = bos->current_cursor;
	if (cursor > left) {
		/* Bits can be added to the buffer as a whole. */
		bos->current_buffer |= (bits << (cursor - left));
		bos->current_cursor -= left;
	} else {
		/* Bits do not fit in the buffer and must be split to be printed. */
		uint_fast8_t append = (uint_fast8_t) (left - cursor);
		uint_fast64_t buffer = outputstream_endian_64(bos->current_buffer | (uint_fast64_t) (bits >> append));
		fwrite_unlocked(&buffer, 8, 1, bos->channel);
		bos->current_buffer = ((bits & bitmask_n_offset(append, 0)) << (64 - append));
		bos->current_cursor = (uint_fast8_t) (BIT_OUTPUT_STREAM_SIZE_BITS - append);
	}
}

void bos_flush(bit_output_stream *bos) {
	if (bos->current_cursor != BIT_OUTPUT_STREAM_SIZE_BITS) {
		bos_print_buffer(bos);
	}
	fflush(bos->channel);
}

void bos_free(bit_output_stream *bos) {
	if (bos->channel) {
		funlockfile(bos->channel);
	}
	free(bos);
}

size_t bos_pad(bit_output_stream *bos) {
	size_t padding = (size_t) (bos->current_cursor % 8);
	if (padding != BITS_IN_BYTE) {
		bos_print_buffer(bos);
		return padding;
	}
	return 0;
}
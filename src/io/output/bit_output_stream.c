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
#include "../input/byte_input_stream.h"

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
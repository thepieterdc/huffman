/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_output_stream.h"
#include "../../util/memory.h"
#include "../../util/binary.h"

/**
 * Prints the contents of the internal buffer.
 *
 * @param bos the bit output stream
 */
static inline void print_buffer(bit_output_stream *bos) {
	putc_unlocked(bos->current_byte, bos->channel);
	bos->current_byte = 0;
	bos->current_cursor = BITS_IN_BYTE;
}

bit_output_stream *bos_create(FILE *channel) {
	bit_output_stream *ret = (bit_output_stream *) mallocate(sizeof(bit_output_stream));
	ret->channel = channel;
	ret->current_byte = 0;
	ret->current_cursor = BITS_IN_BYTE;
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

void bos_feed_bit(bit_output_stream *bos, bit b) {
	bos->current_byte |= (b << (--bos->current_cursor));
	if (bos->current_cursor == 0) {
		print_buffer(bos);
	}
}

void bos_feed_bits(bit_output_stream *bos, uint_fast64_t bits, uint_fast8_t left) {
	do {
		if (bos->current_cursor == BITS_IN_BYTE && left == BITS_IN_BYTE) {
			putc_unlocked((byte) bits, bos->channel);
			return;
		} else if (left < bos->current_cursor) {
			bos->current_byte |= (bits << (bos->current_cursor -= left));
			return;
		} else {
			uint_fast8_t shift = left - bos->current_cursor;
			bos->current_byte |= (bits & (bitmask_n(bos->current_cursor) << shift)) >> shift;
			left -= bos->current_cursor;
			print_buffer(bos);
		}
	} while(left > 0);
}

void bos_feed_byte(bit_output_stream *bos, byte b) {
	if (bos->current_cursor == BITS_IN_BYTE) {
		putc_unlocked(b, bos->channel);
	} else {
		bos->current_byte |= (b >> (BITS_IN_BYTE - bos->current_cursor));
		putc_unlocked(bos->current_byte, bos->channel);
		bos->current_byte = (b << bos->current_cursor);
	}
}

void bos_flush(bit_output_stream *bos) {
	if (bos->current_cursor != BITS_IN_BYTE) {
		print_buffer(bos);
	}
	fflush(bos->channel);
}

void bos_free(bit_output_stream *bos) {
	if(bos->channel) {
		funlockfile(bos->channel);
	}
	free(bos);
}

size_t bos_pad(bit_output_stream *bos) {
	size_t padding = bos->current_cursor;
	if (padding != BITS_IN_BYTE) {
		print_buffer(bos);
		return padding;
	}
	return 0;
}
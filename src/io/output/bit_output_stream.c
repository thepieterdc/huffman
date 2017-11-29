/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_output_stream.h"
#include "../../util/memory.h"
#include "../../util/binary.h"

#define BIT_OUTPUT_STREAM_SIZE_BITS 64
#define BIT_OUTPUT_STREAM_SIZE_BYTES 8

#if __BYTE_ORDER == __BIG_ENDIAN
#define outputstream_endian_64(val) val
#else
#define outputstream_endian_64(val) \
( (((val) >> 56) & 0x00000000000000FF) | (((val) >> 40) & 0x000000000000FF00) | \
  (((val) >> 24) & 0x0000000000FF0000) | (((val) >>  8) & 0x00000000FF000000) | \
  (((val) <<  8) & 0x000000FF00000000) | (((val) << 24) & 0x0000FF0000000000) | \
  (((val) << 40) & 0x00FF000000000000) | (((val) << 56) & 0xFF00000000000000) )
#endif

/**
 * Prints the entire internal buffer.
 *
 * @param bos the bit output stream
 */
static inline void print_buffer(bit_output_stream *bos) {
	uint_fast64_t buffer = outputstream_endian_64(bos->current_buffer);
	fwrite_unlocked(&buffer, bos_current_byte(bos->current_cursor), 1, bos->channel);
	bos->current_buffer = 0;
	bos->current_cursor = BIT_OUTPUT_STREAM_SIZE_BITS;
}

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

void bos_feed_bit(bit_output_stream *bos, bit b) {
	bos->current_buffer |= ((uint_fast64_t) b << (--bos->current_cursor));
	if (bos->current_cursor == 0) {
		fprintf(stderr, "Flushed\n");
		print_buffer(bos);
	}
}

void bos_feed_bits(bit_output_stream *bos, uint_fast64_t bits, uint_fast8_t left) {
	register size_t cursor = bos->current_cursor;
	if (cursor > left) {
		/* Bits can be added to the buffer as a whole. */
		bos->current_buffer |= (bits << (cursor - left));
		bos->current_cursor -= left;
	} else {
		/* Bits do not fit in the buffer and must be split to be printed. */
		fprintf(stderr, "Can print another %d bits of %d of %s\n", cursor, left, byte_to_bitstring((byte) bits));
		for(size_t i = cursor; i > 0; --i) {
			fprintf(stderr, "Printed %d -> %d, mask %s\n", i, (bit) (bits & (1 << (left-i))), byte_to_bitstring(1 << (i)));
			bos_feed_bit(bos, (bit) (bits & (1 << (i - 1))));
		}
		fprintf(stderr, "Now printing remaining %d bits of %d of %s\n", left-cursor, left, byte_to_bitstring((byte) bits));
		for(size_t i = left-cursor; i > 0; --i) {
			fprintf(stderr, "Printed %d -> %d\n", i, (bit) (bits & (1 << (i-1))));
			bos_feed_bit(bos, (bit) (bits & (1 << (i-1))));
		}
//		bos->current_buffer |= (bits >> (left - cursor));
//		uint_fast64_t buffer = outputstream_endian_64(bos->current_buffer);
//		fwrite_unlocked(&buffer, BIT_OUTPUT_STREAM_SIZE_BYTES, 1, bos->channel);
//		bos->current_buffer = ((uint_fast64_t) (bits << (BIT_OUTPUT_STREAM_SIZE_BITS - left + cursor)));
//		bos->current_cursor = (uint_fast8_t) (BIT_OUTPUT_STREAM_SIZE_BITS - left + cursor);
	}
}

void bos_flush(bit_output_stream *bos) {
	if (bos->current_cursor != BIT_OUTPUT_STREAM_SIZE_BITS) {
		print_buffer(bos);
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
		print_buffer(bos);
		return padding;
	}
	return 0;
}
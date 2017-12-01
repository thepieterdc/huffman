/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_BITOUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_BITOUTPUTSTREAM_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>
#include "../../util/binary.h"
#include "../../datatypes/huffman_code.h"

#define BIT_OUTPUT_STREAM_SIZE_BITS 64
#define BIT_OUTPUT_STREAM_SIZE_BYTES 8

#define OUTPUT_BUFFER_SIZE KIBIBYTE(32)

/**
 * Fixes the endianness to print 64 bits.
 */
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
 * An output stream for bits.
 */
typedef struct {
	FILE *channel;
	uint_fast64_t current_buffer;
	uint_fast8_t current_cursor;
} bit_output_stream;

/**
 * Creates a new output stream for bytes.
 *
 * @param channel the output channel to flush to
 * @return the created byte output stream
 */
bit_output_stream *bos_create(FILE *channel);

/**
 * Calculates the amount of bytes in the internal buffer
 *
 * @param cursor the current cursor
 * @return the amount of bytes
 */
#define bos_current_byte(cursor) (size_t) (BIT_OUTPUT_STREAM_SIZE_BYTES - ((cursor) >> 3))

/**
 * Feeds the stream with one bit.
 *
 * @param bos the bit output stream
 * @param b the bit to feed
 */
#define bos_feed_bit(bos, b) ({\
        (bos)->current_buffer |= ((uint_fast64_t) (b) << (--(bos)->current_cursor));\
        if ((bos)->current_cursor == 0) bos_print_buffer(bos);\
})

/**
 * Feeds the stream with multiple bits.
 *
 * @param bos the bit output stream
 * @param bits the bits to feed
 * @param amount the amount of bits to feed
 */
#define bos_feed_bits(bos, bits, left) ({\
	register size_t cursor = (bos)->current_cursor;\
	if (cursor > (left)) {\
        (bos)->current_buffer |= ((bits) << (cursor - (left)));\
        (bos)->current_cursor -= (left);\
	} else {\
		uint_fast8_t append = (uint_fast8_t) ((left) - cursor);\
		uint_fast64_t buffer = outputstream_endian_64((bos)->current_buffer | (uint_fast64_t) ((bits) >> append));\
		fwrite_unlocked(&buffer, 8, 1, (bos)->channel);\
        (bos)->current_buffer = (((bits) & bitmask_n_offset(append, 0)) << (64 - append));\
        (bos)->current_cursor = (uint_fast8_t) (BIT_OUTPUT_STREAM_SIZE_BITS - append);\
	}\
})

/**
 * Flushes the output buffer.
 *
 * @param bos the byte output stream
 */
void bos_flush(bit_output_stream *bos);

/**
 * Frees the memory allocated by the bit output stream.
 *
 * @param bos the bit output stream
 */
void bos_free(bit_output_stream *bos);

/**
 * Padds the current byte to a whole byte and adds it to the stream.
 *
 * @param bos the bit output stream
 * @return the amount of bits that were added at the right
 */
size_t bos_pad(bit_output_stream *bos);

/**
 * Prints the entire internal buffer.
 *
 * @param bos the bit output stream
 */
#define bos_print_buffer(bos) ({\
    uint_fast64_t bos_buffer = outputstream_endian_64((bos)->current_buffer);\
    fwrite_unlocked(&bos_buffer, bos_current_byte((bos)->current_cursor), 1, (bos)->channel);\
    (bos)->current_buffer = 0;\
    (bos)->current_cursor = BIT_OUTPUT_STREAM_SIZE_BITS;\
})

#endif /* HUFFMAN_IO_OUTPUT_BITOUTPUTSTREAM_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_BITOUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_BITOUTPUTSTREAM_H

#include <stdio.h>
#include "../../util/binary.h"
#include "../../datatypes/huffman_code.h"

#define OUTPUT_BUFFER_SIZE KIBIBYTE(32)

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
void bos_feed_bit(bit_output_stream *bos, bit b);

/**
 * Feeds the stream with multiple bits.
 *
 * @param bos the bit output stream
 * @param bits the bits to feed
 * @param amount the amount of bits to feed
 */
void bos_feed_bits(bit_output_stream *bos, uint_fast64_t bits, uint_fast8_t amount);

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

#endif /* HUFFMAN_IO_OUTPUT_BITOUTPUTSTREAM_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_BIT_OUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_BIT_OUTPUTSTREAM_H

#include "byte_output_stream.h"
#include "../../datatypes/uint256_t.h"
#include "../../datatypes/huffman_code.h"

/**
 * An output stream for bits.
 */
typedef struct {
	byte_output_stream *stream;
	byte current_byte;
	size_t current_cursor;
} bit_output_stream;

/**
 * Gets the amount of items in the bit output stream buffer.
 *
 * @param bos the bit output stream
 * @return the amount of items in the bit output stream buffer
 */
size_t bos_count(bit_output_stream *bos);

/**
 * Creates a new output stream for bytes.
 *
 * @param channel the output channel to flush to
 * @return the created byte output stream
 */
bit_output_stream *bos_create(FILE *channel);

/**
 * Feeds the stream with one bit.
 *
 * @param bos the bit output stream
 * @param b the bit to feed
 */
void bos_feed_bit(bit_output_stream *bos, bit b);

/**
 * Feeds the stream with one byte.
 *
 * @param bos the bit output stream
 * @param b the byte to feed
 */
void bos_feed_byte(bit_output_stream *bos, byte b);

/**
 * Feeds the stream with a Huffman code.
 *
 * @param bos the bit output stream
 * @param hc the Huffman code to feed
 */
void bos_feed_huffmancode(bit_output_stream *bos, huffman_code *hc);

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

#endif /* HUFFMAN_IO_OUTPUT_BIT_OUTPUTSTREAM_H */
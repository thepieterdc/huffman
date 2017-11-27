/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_INPUT_BIT_INPUTSTREAM_H
#define HUFFMAN_IO_INPUT_BIT_INPUTSTREAM_H

#include "byte_input_stream.h"


/**
 * An input stream for bits.
 */
struct bit_input_stream;

/**
 * A function that reads a byte
 */
typedef byte (*_bit_input_feed_byte_function)(struct byte_input_stream *);

/**
 * An input stream for bits.
 */
typedef struct bit_input_stream {
	byte_input_stream *stream;
	byte current_byte;
	size_t current_cursor;
	_bit_input_feed_byte_function feedFn;
} bit_input_stream;

/**
 * Gets the amount of bits left in the current byte.
 *
 * @param bis
 * @return
 */
#define bis_bits_left(bis) (BITS_IN_BYTE - (bis)->current_cursor)

/**
 * Clears the current byte.
 *
 * @param bis the input stream
 */
void bis_clear_current_byte(bit_input_stream *bis);

/**
 * Creates a new byte input stream.
 *
 * @param channel the encapsulated stream to feed off
 * @param retain false to clear the buffer when full, true to expand it
 * @return the created byte input stream
 */
bit_input_stream *bis_create(FILE *channel, bool retain);

/**
 * Clears the entire input stream.
 *
 * @param bis the bit input stream
 */
void bis_flush(bit_input_stream *bis);

/**
 * Frees the memory allocated by the bit input stream.
 *
 * @param bis the bit input stream
 */
void bis_free(bit_input_stream *bis);

/**
 * Returns n bits from the buffer. Does not remove those bits from the buffer.
 *
 * @param bis the bit input stream
 * @param n the amount of bits to retrieve
 * @return n bits from the buffer
 */
#define bis_get_n_bits(bis, n) ((uint_fast8_t) ((bis)->current_byte << (bis)->current_cursor) >> (BITS_IN_BYTE-(n)))

/**
 * Reads one bit from the bit input stream
 *
 * @param bis the bit input stream
 * @return the bit
 */
bit bis_read_bit(bit_input_stream *bis);

/**
 * Reads one byte from the bit input stream
 *
 * @param bis the bit input stream
 * @return the byte
 */
byte bis_read_byte(bit_input_stream *bis);

/**
 * Rewinds the internal cursor by n bits, cannot retrieve lost bytes.
 *
 * @param bis the bit input stream
 * @param n the amount of bits to rewind
 */
#define bis_rewind(bis, n) ((bis)->current_cursor -= (n))

#endif /* HUFFMAN_IO_INPUT_BIT_INPUTSTREAM_H */
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
typedef struct {
	byte_input_stream *stream;
	byte current_byte;
	size_t current_cursor;
} bit_input_stream;

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
 * Frees the memory allocated by the bit input stream.
 *
 * @param bis the bit input stream
 */
void bis_free(bit_input_stream *bis);

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

#endif /* HUFFMAN_IO_INPUT_BIT_INPUTSTREAM_H */
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
	byte_input_stream *bytestream;
	
	byte current_byte;
	size_t current_cursor;
	bool empty;
} bit_input_stream;

/**
 * Clears the current byte from the buffer.
 *
 * @param bis the input stream to clear
 */
void bis_clear_buffer(bit_input_stream *bis);

/**
 * Gets the amount of items in the bit input stream buffer.
 *
 * @param bis the bit input stream
 * @return the amount of items in the bit input stream buffer
 */
size_t bis_count(bit_input_stream *bis);

/**
 * Creates a new input stream for bytes.
 *
 * @param channel the data to feed the stream from
 * @return the created byte input stream
 */
bit_input_stream *bis_create(FILE *channel);

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
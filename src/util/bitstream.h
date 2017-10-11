/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */


#ifndef HUFFMAN_UTIL_BITSTREAM_H
#define HUFFMAN_UTIL_BITSTREAM_H

#include <unistd.h>
#include <stdbool.h>
#include "binary.h"
#include "../datastructures/queue.h"

/**
 * A bitstream.
 */
typedef struct {
	queue *buffer;
	byte current_byte;
	size_t current_byte_cursor;
} bitstream;

/**
 * Adds a bit to the current byte and eventually to the buffer.
 *
 * @param bs the bitstream
 * @param b the bit to add
 */
void bs_add_bit(bitstream *bs, bit b);

/**
 * Adds a byte to the current buffer.
 *
 * @param bs the bitstream
 * @param b the byte to add
 */
void bs_add_byte(bitstream *bs, byte b);

/**
 * Creates a new bitstream.
 *
 * @return the newly created bitstream
 */
bitstream *bs_create();

/**
 * Frees the memory allocated by the bitstream.
 *
 * @param bs the bitstream to free
 */
void bs_free(bitstream *bs);

#endif /* HUFFMAN_UTIL_BITSTREAM_H */
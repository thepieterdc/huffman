/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */


#ifndef HUFFMAN_UTIL_BITSTREAM_H
#define HUFFMAN_UTIL_BITSTREAM_H

#include <unistd.h>

/**
 * A bitstream.
 */
typedef struct {
	int *buffer;
	int current_byte;
	size_t current_byte_cursor;
} bitstream;

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
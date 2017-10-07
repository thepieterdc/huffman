/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_BITPRINTER_H
#define HUFFMAN_UTIL_BITPRINTER_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * A bitprinter.
 */
typedef struct {
	int buffer;
	size_t cursor;
	FILE *channel;
} bitprinter;

/**
 * Creates a new bitprinter.
 *
 * @param channel the output channel to print to
 * @return pointer to the bitprinter
 */
bitprinter *bitprinter_create(FILE *channel);

/**
 * Adds a bit to the printer and flushes if necessary.
 *
 * @param bp the bitprinter
 * @param bit the bit to add
 */
void bitprinter_add_bit(bitprinter *bp, bool bit);

/**
 * Flushes the contents of the printer to the output channel.
 *
 * @param bp the bitprinter
 */
void bitprinter_flush(bitprinter *bp);

/**
 * Frees the memory allocated by the bitprinter.
 *
 * @param bp the bitprinter
 * @param flush true to force flush the remaining buffer contents
 */
void bitprinter_free(bitprinter *bp, bool flush);

#endif /* HUFFMAN_UTIL_BITPRINTER_H */
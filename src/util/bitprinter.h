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
	FILE *channel;
	size_t size; /* current amount of bits stored. */
	int bits; /* current bits stored. */
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
 * @param bit the bit to add
 */
void add_bit(bool bit);

/**
 * Flushes the contents of the printer to the output channel.
 */
void flush();

#endif /* HUFFMAN_UTIL_BITPRINTER_H */
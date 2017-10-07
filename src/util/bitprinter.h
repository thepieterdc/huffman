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
#include "string.h"

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
bitprinter *bp_create(FILE *channel);

/**
 * Flushes the contents of the printer to the output channel.
 *
 * @param bp the bitprinter
 */
void bp_flush(bitprinter *bp);

/**
 * Frees the memory allocated by the bitprinter.
 *
 * @param bp the bitprinter
 * @param flush true to force flush the remaining buffer contents
 */
void bp_free(bitprinter *bp, bool flush);

/**
 * Adds a bit to the printer and flushes if necessary.
 *
 * @param bp the bitprinter
 * @param bit the bit to add
 *
 * @example bp_print_bit(bp, 1);
 */
void bp_print_bit(bitprinter *bp, bool bit);

/**
 * Adds a string of bits to the printer and flushes if necessary.
 *
 * @param bp the bitprinter
 * @param bitstring the string to print
 *
 * @example bp_print_bitstring(bp, "101000011");
 */
void bp_print_bitstring(bitprinter *bp, string bitstring);

#endif /* HUFFMAN_UTIL_BITPRINTER_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_STANDARD_H
#define HUFFMAN_ALGORITHMS_STANDARD_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>

/**
 * Standard Huffman compression.
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_standard_compress(FILE *input, FILE *output);

/**
 * Standard Huffman decompression.
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_standard_decompress(FILE *input, FILE *output);

#endif /* HUFFMAN_ALGORITHMS_STANDARD_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_TWOPASS_H
#define HUFFMAN_ALGORITHMS_TWOPASS_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>

/**
 * Two-pass Huffman compression.
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_twopass_compress(FILE *input, FILE *output);

/**
 * Two-pass Huffman decompression.
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_twopass_decompress(FILE *input, FILE *output);

#endif /* HUFFMAN_ALGORITHMS_TWOPASS_H */
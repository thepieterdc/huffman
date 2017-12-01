/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_ADAPTIVE_H
#define HUFFMAN_ALGORITHMS_ADAPTIVE_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>

/**
 * Adaptive Huffman compression (FGK).
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_adaptive_compress(FILE *input, FILE *output);

/**
 * Adaptive Huffman decompression (FGK).
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_adaptive_decompress(FILE *input, FILE *output);

#endif /* HUFFMAN_ALGORITHMS_ADAPTIVE_H */
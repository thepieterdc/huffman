/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_SLIDING_H
#define HUFFMAN_ALGORITHMS_SLIDING_H

#include <stdio.h>

#define HUFFMAN_SLIDING_WINDOWSIZE 5

/**
 * Adaptive Huffman compression (sliding window).
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_sliding_compress(FILE *input, FILE *output);

/**
 * Adaptive Huffman decompression (sliding window).
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_sliding_decompress(FILE *input, FILE *output);

#endif /* HUFFMAN_ALGORITHMS_SLIDING_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_SLIDING_H
#define HUFFMAN_ALGORITHMS_SLIDING_H

#include <stdio.h>

/**
 * @internal
 *
 * @param input the input data to process
 * @param output the output channel
 * @param window_size the size of the sliding window
 */
void __huffman_sliding_compress(FILE *input, FILE *output, size_t window_size);

/**
 * Adaptive Huffman compression (sliding window).
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_sliding_compress(FILE *input, FILE *output);

/**
 * @internal
 *
 * @param input the input data to process
 * @param output the output channel
 * @param window_size the size of the sliding window
 */
void __huffman_sliding_decompress(FILE *input, FILE *output, size_t window_size);

/**
 * Adaptive Huffman decompression (sliding window).
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_sliding_decompress(FILE *input, FILE *output);

#endif /* HUFFMAN_ALGORITHMS_SLIDING_H */
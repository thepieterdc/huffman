/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_BLOCKWISE_H
#define HUFFMAN_ALGORITHMS_BLOCKWISE_H

#include <stdio.h>

/**
 * Blockwise Huffman compression.
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_blockwise_compress(FILE *input, FILE *output);

/**
 * Blockwise Huffman decompression.
 *
 * @param input the input data to process
 * @param output the output channel
 */
void huffman_blockwise_decompress(FILE *input, FILE *output);

#endif /* HUFFMAN_ALGORITHMS_BLOCKWISE_H */
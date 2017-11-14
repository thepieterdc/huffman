/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "sliding.h"

void huffman_adaptive_compress(FILE *input, FILE *output) {
	__huffman_sliding_compress(input, output, 0);
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	__huffman_sliding_decompress(input, output, 0);
}
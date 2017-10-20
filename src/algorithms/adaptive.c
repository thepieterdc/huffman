/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"
#include "../util/logging.h"
#include "../datastructures/huffman_tree.h"
#include "../util/errors.h"

void huffman_adaptive_compress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(NULL);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	info("Huffman adaptive decompress");
}
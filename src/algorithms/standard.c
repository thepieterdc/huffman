/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../datastructures/min_heap.h"
#include "../datastructures/huffman_tree/huffman_node.h"
#include "../datastructures/huffman_tree/huffman_tree.h"
#include "util/standard.h"
#include "../util/logging.h"
#include "../util/errors.h"
#include "../io/input/bit_input_stream.h"
#include "util/common.h"

void huffman_standard_compress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(input, true);
	byis_consume(inputStream);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Determine the frequencies of each character. */
	uint_fast64_t frequencies[HUFFMAN_MAX_LEAVES] = {0};
	
	while (inputStream->cursor < inputStream->buffer_size) {
		frequencies[byis_read_unsafe(inputStream)]++;
	}
	
	/* Failsafe for empty input. */
	if (inputStream->buffer_size == 0) {
		error(ERROR_END_OF_INPUT);
	}
	
	/* Create a new empty Huffman tree. */
	huffman_tree *tree = standard_build_tree_from_frequencies(frequencies);
	huffmantree_set_codes(tree);
	
	/* Print the Huffman tree and apply padding. */
	standard_print_tree(tree->root, outputStream);
	bos_pad(outputStream);
	
	/* Print the characters from left to right. */
	standard_print_characters(tree->root, outputStream);
	
	/* Rewind the input. */
	inputStream->cursor = 0;
	
	/* Create two dictionaries for fast lookups. */
	bool data_is_random = true;
	uint_fast64_t codes[HUFFMAN_MAX_LEAVES] = {0};
	uint_fast8_t codelengths[HUFFMAN_MAX_LEAVES] = {0};
	for (size_t i = 0; i < HUFFMAN_MAX_LEAVES; ++i) {
		if (tree->leaves[i]) {
			codes[i] = tree->leaves[i]->code->code;
			codelengths[i] = tree->leaves[i]->code->length;
			if (codelengths[i] != BITS_IN_BYTE) {
				data_is_random = false;
			}
		} else {
			data_is_random = false;
		}
	}
	
	/* Encode the input. */
	if (data_is_random) {
		standard_encode_random(inputStream, output, codes);
	} else {
		standard_encode_regular(inputStream, outputStream, codes, codelengths);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = BITS_IN_BYTE - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	putc_unlocked((byte) padding, output);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	huffmantree_free(tree);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_standard_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, true);
	byis_consume(inputStream->stream);
	
	/* Prepare the output channel. */
	huffman_prepare_output(output);
	
	/* Build up the Huffman tree. */
	huffman_tree *tree = huffmantree_create(NULL);
	tree->root->code = huffmancode_create();
	uint_fast8_t max_code = (uint_fast8_t) (standard_build_tree_from_bits(tree->root, inputStream, true) - 1);
	
	/* Clear the remaining padding bits. */
	bis_clear_current_byte(inputStream);
	
	/* Assign characters to leaves. */
	standard_assign_characters(tree, inputStream);
	
	/* Decode every code in the input string. */
	if (standard_data_is_random(tree)) {
		standard_decode_random(inputStream->stream, output, tree);
	} else {
		standard_decode_regular(inputStream, output, tree, max_code);
	}
	
	/* Flush the output buffer. */
	fflush(output);
	funlockfile(output);
	
	/* Cleanup allocated memory. */
	huffmantree_free(tree);
	bis_free(inputStream);
}

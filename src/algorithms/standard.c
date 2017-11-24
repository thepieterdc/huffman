/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

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
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Determine the frequencies of each character. */
	uint_fast64_t frequencies[HUFFMAN_MAX_LEAVES] = {0};
	
	while (inputStream->cursor <= inputStream->buffer_size) {
		frequencies[byis_read(inputStream)]++;
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
	uint_fast64_t codes[HUFFMAN_MAX_LEAVES] = {0};
	uint_fast8_t codelengths[HUFFMAN_MAX_LEAVES] = {0};
	for (size_t i = 0; i < HUFFMAN_MAX_LEAVES; ++i) {
		if(tree->leaves[i]) {
			codes[i] = tree->leaves[i]->code->code;
			codelengths[i] = tree->leaves[i]->code->length;
		}
	}
	
	/* Encode the input. */
	byte b = byis_read_dirty(inputStream);
	while (inputStream->cursor <= inputStream->buffer_size) {
		bos_feed_bits(outputStream, codes[b], codelengths[b]);
		b = byis_read_dirty(inputStream);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	huffmantree_free(tree);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_standard_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Prepare the output channel. */
	huffman_prepare_output(output);
	
	/* Build up the Huffman tree. */
	huffman_tree *tree = huffmantree_create(NULL);
	tree->root->code = huffmancode_create();
	
	standard_build_tree_from_bits(tree->root, inputStream, true);
	
	/* Clear the remaining padding bits. */
	bis_clear_current_byte(inputStream);
	
	/* Assign characters to leaves. */
	standard_assign_characters(tree, inputStream);
	
	/* Decode every code in the input string. */
	while (inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
		putc_unlocked(standard_decode_character(tree->root, inputStream), output);
	}
	
	/* Decode the remaining bytes. */
	size_t indicator = huffman_finalize_input(inputStream);
	while (inputStream->current_cursor < indicator) {
		putc_unlocked(standard_decode_character(tree->root, inputStream), output);
	}
	
	/* Flush the output buffer. */
	fflush(output);
	funlockfile(output);
	
	/* Cleanup allocated memory. */
	huffmantree_free(tree);
	bis_free(inputStream);
}

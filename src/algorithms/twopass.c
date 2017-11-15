/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "twopass.h"
#include "../util/logging.h"
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../util/errors.h"
#include "../datastructures/huffman_tree/huffman_tree.h"
#include "../datastructures/min_heap.h"
#include "util/standard.h"
#include "util/twopass.h"
#include "../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "util/adaptive.h"
#include "util/sliding.h"

void huffman_twopass_compress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(NULL, true);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Determine the frequencies of each character. */
	uint_least64_t frequencies[256] = {0};
	
	int in;
	while ((in = getc(input)) != EOF) {
		frequencies[in]++;
		byis_feed_byte(inputStream, (byte) in);
	}
	
	/* Close the input channel. */
	fclose(input);
	
	/* Failsafe for empty input. */
	if (inputStream->buffer_size == 0) {
		error(ERROR_END_OF_INPUT);
	}
	
	/* Create a new Adaptive Huffman tree. */
	adaptive_huffman_tree aht;
	huffman_tree *tree = standard_build_tree_from_frequencies(frequencies);
	
	/* Print the Huffman tree and apply padding. */
	standard_print_tree(tree->root, outputStream);
	bos_pad(outputStream);
	
	/* Print the characters from left to right. */
	standard_print_characters(tree->root, outputStream);
	
	/* Convert the tree into an Adaptive Huffman tree. */
	twopass_parse_tree(&aht, tree);
	
	/* Encode the input. */
	byte z = byis_read(inputStream);
	while (inputStream->cursor <= inputStream->buffer_size) {
		/* Output the encoded character. */
		adaptive_print_code(tree->leaves[z], outputStream);
		
		/* Update the tree, don't update if there is only 1 character leaf left. */
		if(aht.amt_nodes > 2) {
			sliding_update_tree(&aht, z);
		}

		z = byis_read(inputStream);
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

void huffman_twopass_decompress(FILE *input, FILE *output) {
	info("Huffman TwoPass decompress.");
}
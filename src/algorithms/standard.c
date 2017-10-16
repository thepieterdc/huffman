/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "standard.h"
#include "../util/logging.h"
#include "../io/input/byte_input_stream.h"
#include "../datastructures/min_heap.h"
#include "../datastructures/huffman_tree.h"
#include "../io/output/bit_output_stream.h"

void huffman_standard_compress(FILE *input, FILE *output) {
	/* Reset the order numbers. */
	huffman_reset_ordercounter();
	
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(NULL);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Determine the frequencies of each byte. */
	uint_least64_t frequencies[256] = {0};
	
	int in;
	while ((in = getc(input)) != EOF) {
		frequencies[in]++;
		byis_feed(inputStream, (byte) in);
	}
	
	/* Add all bytes to a heap. */
	min_heap *heap = minheap_create(256);
	for (size_t i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			huffman_node *leaf = huffman_create_leaf((byte) i, frequencies[i]);
			minheap_insert(heap, leaf->weight, leaf);
		}
	}
	
	/* Create the Huffman tree. */
	while (heap->size > 1) {
		huffman_node *left = minheap_extract_min(heap);
		huffman_node *right = minheap_extract_min(heap);
		huffman_node *parent = huffman_create_node(left, right);
		minheap_insert(heap, parent->weight, parent);
	}
	
	huffman_node *tree = minheap_find_min(heap);
	
	/* Print the Huffman tree. */
	huffman_print_tree(tree, outputStream);
	
	/* Create a dictionary to save the codes for fast encoding. */
	huffman_code codes_dictionary[256];
	/* */

//	char **codes_dictionary = (char **) malloc(256 * sizeof(char *));
//	dynamic_array *volgorde_letters = da_create();
//
//	// Print tree
//	print_tree_update_codes(tree, "\0", codes_dictionary, volgorde_letters, bp);
//	bp_flush(bp);
//
//	// Print letters DFS based
//	for (int i = 0; i < volgorde_letters->size; ++i) {
//		printf("%c", (char) (int) da_get(volgorde_letters, (size_t) i));
//	}
//	fflush(stdout);
//
//	// Print encoded word
//	for (int i = 0; i < raw_string->size; ++i) {
//		bp_print_bitstring(bp, codes_dictionary[(int) da_get(raw_string, (size_t) i)]);
//	}
//	bp_flush(bp);
	
	bos_flush(outputStream);
	
	minheap_free(heap);
	
	huffman_free(tree);
	
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_standard_decompress(FILE *input, FILE *output) {
	info("Using algorithm: Standard Huffman.");
	info("Mode: Decompress");
}
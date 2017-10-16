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
#include "../io/input/input_stream.h"

/**
 * Traverses the tree in a DFS manner and prints all bytes while filling the
 * code dictionary.
 *
 * @param root the root of the tree
 * @param dictionary the dictionary to fill
 * @param out the output stream
 */
static void
build_dictionary(huffman_node *root, huffman_code *current_code, huffman_code **dictionary, bit_output_stream *out) {
	if (root->type == LEAF) {
		dictionary[root->data] = current_code;
//		bos_feed_byte(out, root->data);
	} else {
		huffman_code *leftcode = huffmancode_create_left(current_code);
		build_dictionary(root->left, leftcode, dictionary, out);
		huffman_code *rightcode = huffmancode_create_right(current_code);
		build_dictionary(root->right, rightcode, dictionary, out);
		huffmancode_free(current_code);
	}
}

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
	
	/* Print the Huffman tree and apply padding. */
//	huffman_print_tree(tree, outputStream);
//	bos_pad(outputStream);
	
	/* Create a dictionary to save the codes for fast encoding. */
	huffman_code *codes_dictionary[256];
	
	/* Print the characters from left to right and fill the dictionary. */
	build_dictionary(tree, huffmancode_create(), codes_dictionary, outputStream);

	/* Encode every character in the input string. */
	while(!byis_empty(inputStream)) {
		huffman_code *encode = codes_dictionary[byis_read(inputStream)];
		bos_feed_huffmancode(outputStream, encode);
	}
	
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
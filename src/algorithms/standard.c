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

void huffman_standard_compress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(NULL);
	
	size_t *frequencies = (size_t *) malloc(256 * sizeof(size_t));
	
	int in;
	while ((in = getc(input)) != EOF) {
		frequencies[in]++;
		byis_feed(inputStream, (byte) in);
	}
	
	min_heap *heap = minheap_create(256);
	for (size_t i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			huffman_node *leaf = huffman_create_leaf((byte) i, frequencies[i]);
			minheap_insert(heap, leaf->weight, leaf);
		}
	}
//
//	while (heap->size > 1) {
//		huffman_node *minnode1 = da_get(heap, 0);
//		int minnode1_idx = 0;
//		for (int i = 1; i < heap->size; ++i) {
//			huffman_node *node = da_get(heap, (size_t) i);
//			if (node->weight < minnode1->weight) {
//				minnode1 = node;
//				minnode1_idx = i;
//			}
//		}
//		da_remove_index(heap, (size_t) minnode1_idx);
//
//		huffman_node *minnode2 = da_get(heap, 0);
//		int minnode2_idx = 0;
//		for (int i = 1; i < heap->size; ++i) {
//			huffman_node *node = da_get(heap, (size_t) i);
//			if (node->weight < minnode2->weight) {
//				minnode2 = node;
//				minnode2_idx = i;
//			}
//		}
//		da_remove_index(heap, (size_t) minnode2_idx);
//
//		huffman_node *node = (huffman_node *) malloc(sizeof(huffman_node));
//		node->type = NODE;
//		node->left = minnode1;
//		node->right = minnode2;
//		node->weight = minnode1->weight + minnode2->weight;
//		da_add(heap, node);
//	}
//
//	huffman_node *tree = da_get(heap, 0);
//
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
}

void huffman_standard_decompress(FILE *input, FILE *output) {
	info("Using algorithm: Standard Huffman.");
	info("Mode: Decompress");
}
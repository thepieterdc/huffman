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
#include "../datastructures/huffman_tree/adaptive_huffman_tree.h"

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
	huffman_tree *tree = huffmantree_create_empty();
	
	/* Add all bytes to a heap. */
	min_heap *heap = minheap_create(256);
	for (size_t i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			huffman_node *leaf = huffmannode_create_leaf((byte) i, frequencies[i]);
			tree->leaves[i] = leaf;
			minheap_insert(heap, leaf->weight, leaf);
		}
	}
	
	/* Failsafe for strings containing 1 character. */
	if (heap->size == 1) {
		huffman_node *nullnode = huffmannode_create_leaf(0, 1);
		minheap_insert(heap, nullnode->weight, nullnode);
	}
	
	/* Fill the Huffman tree. */
	while (heap->size > 1) {
		huffman_node *left = minheap_extract_min(heap);
		huffman_node *right = minheap_extract_min(heap);
		huffman_node *parent = huffmannode_create_node(left, right);
		minheap_insert(heap, parent->weight, parent);
	}
	
	tree->root = minheap_find_min(heap);
	
	/* Convert the tree into an Adaptive Huffman tree. */
	adaptivehuffmantree_initialise(&aht, tree);
	
	/* Print the Huffman tree and apply padding. */
	standard_print_tree(tree->root, outputStream);
	bos_pad(outputStream);
	
	/* Print the characters from left to right. */
	standard_print_characters(tree->root, outputStream);
	
	/* Encode the input. */
	byte z = byis_read(inputStream);
//	while (inputStream->cursor <= inputStream->buffer_size) {
//		byte_queue_push(window, z);
//
//		/* Output the encoded character. */
//		huffman_node *t = adaptive_encode_character(aht, z, outputStream);
//
//		/* Update the tree accordingly. */
//		adaptive_update_tree(aht, t);
//
//		/* Update the tree using the sliding window. */
//		if (window->size > HUFFMAN_SLIDING_WINDOWSIZE) {
//			sliding_update_tree(aht, byte_queue_pop(window));
//		}
//
//		z = byis_read(inputStream);
//	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	minheap_free(heap);
	huffmantree_free(tree);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_twopass_decompress(FILE *input, FILE *output) {
	info("Huffman TwoPass decompress.");
}
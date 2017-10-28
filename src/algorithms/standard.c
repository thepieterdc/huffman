#include <stdio.h>
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../datastructures/min_heap.h"
#include "../datastructures/huffman_tree/huffman_node.h"
#include "../datastructures/huffman_tree/huffman_tree.h"
#include "util/standard.h"
#include "../util/logging.h"
#include "../util/errors.h"

/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

void huffman_standard_compress(FILE *input, FILE *output) {
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
		error(ERROR_EMPTY_INPUT);
	}
	
	/* Create a new empty Huffman tree. */
	huffman_tree *tree = huffmantree_create(NULL);
	
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
	
	huffmantree_set_root(tree, minheap_find_min(heap));
	huffmantree_set_codes(tree);
	
	/* Print the Huffman tree and apply padding. */
	print_tree(tree->root, outputStream);
	bos_pad(outputStream);
	
	/* Print the characters from left to right. */
	print_characters(tree->root, outputStream);
	
	/* Encode every character in the input string. */
	byte b = byis_read(inputStream);
	while (!inputStream->end) {
		huffman_code *encode = tree->leaves[b]->code;
		bos_feed_huffmancode(outputStream, encode);
		b = byis_read(inputStream);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Print how many padding was added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Print the output buffer. */
	bos_flush(outputStream);
	
	/* Cleanup allocated memory. */
	minheap_free(heap);
	huffmantree_free(tree);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_standard_decompress(FILE *input, FILE *output) {
//	/* Create a buffer to store the input. */
//	bit_input_stream *inputStream = bis_create(input);
//
//	/* Create a buffer to store the output. */
//	byte_output_stream *outputStream = byos_create(output);
//
//	/* Failsafe for empty input. */
//	if (bis_empty(inputStream)) {
//		error(ERROR_EMPTY_INPUT);
//	}
//
//	/* Build up the Huffman tree. */
//	huffman_tree *tree = huffmantree_create(NULL);
//	tree->root->code = huffmancode_create();
//
//	build_tree(tree->root, inputStream);
//
//	/* Clear the remaining padding bits. */
//	bis_clear_buffer(inputStream);
//
//	/* Assign characters to codes. */
//	assign_characters(tree->root, inputStream);
//
//	/* Decode every code in the input string. */
//	while (true) {
//		if (bis_count(inputStream) < 16) {
//			byte current = inputStream->current_byte;
//			size_t current_cursor = inputStream->current_cursor;
//			bis_clear_buffer(inputStream);
//			byte next = bis_read_byte(inputStream);
//			decode_final_byte(tree->root, outputStream, current, (size_t) (next - current_cursor));
//			break;
//		} else {
//			byos_feed(outputStream, decode_character(tree->root, inputStream));
//		}
//	}
//
//	/* Flush the output buffer. */
//	byos_flush(outputStream);
//
//	/* Cleanup allocated memory. */
//	huffmantree_free(tree);
//	byos_free(outputStream);
//	bis_free(inputStream);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "standard.h"
#include "util/standard.h"
#include "../util/logging.h"
#include "../io/input/byte_input_stream.h"
#include "../datastructures/min_heap.h"
#include "../io/output/bit_output_stream.h"
#include "../io/input/input_stream.h"
#include "../io/input/bit_input_stream.h"

void huffman_standard_compress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(NULL);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Determine the frequencies of each character. */
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
	huffman_print_tree(tree, outputStream);
	bos_pad(outputStream);
	
	/* Create a dictionary to save the codes for fast encoding. */
	huffman_code *codes_dictionary[256];
	
	/* Print the characters from left to right and fill the dictionary. */
	build_dictionary(tree, huffmancode_create(), codes_dictionary, outputStream);
	
	/* Encode every character in the input string. */
	while (!byis_empty(inputStream)) {
		huffman_code *encode = codes_dictionary[byis_read(inputStream)];
		bos_feed_huffmancode(outputStream, encode);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Print how many padding was added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Print the output buffer. */
	bos_flush(outputStream);
	
	/* Cleanup allocated memory. */
	minheap_free(heap);
	huffman_free(tree);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_standard_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input);
	
	/* Create a buffer to store the output. */
	byte_output_stream *outputStream = byos_create(output);
	
	/* Build up the Huffman tree. */
	huffman_node *tree = huffman_create_node(NULL, NULL);
	tree->code = huffmancode_create();
	
	build_tree(tree, inputStream);
	
	/* Clear the remaining padding bits. */
	bis_clear_buffer(inputStream);
	
	/* Assign characters to codes. */
	assign_characters(tree, inputStream);
	
	/* Decode every code in the input string. */
	while (true) {
		if (bis_count(inputStream) < 16) {
			byte current = inputStream->current_byte;
			size_t current_cursor = inputStream->current_cursor;
			bis_clear_buffer(inputStream);
			byte next = bis_read_byte(inputStream);
			decode_final_byte(tree, outputStream, current, (size_t) (next - current_cursor));
			break;
		} else {
			byos_feed(outputStream, decode_character(tree, inputStream));
		}
	}
	
	/* Flush the output buffer. */
	byos_flush(outputStream);
	
	/* Cleanup allocated memory. */
	huffman_free(tree);
	byos_free(outputStream);
	bis_free(inputStream);
}
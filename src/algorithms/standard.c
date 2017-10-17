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
#include "../io/input/bit_input_stream.h"

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
		bos_feed_byte(out, root->data);
	} else {
		huffman_code *leftcode = huffmancode_create_left(current_code);
		build_dictionary(root->left, leftcode, dictionary, out);
		huffman_code *rightcode = huffmancode_create_right(current_code);
		build_dictionary(root->right, rightcode, dictionary, out);
		huffmancode_free(current_code);
	}
}

void huffman_standard_compress(FILE *input, FILE *output) {
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
	size_t padding = bos_pad(outputStream);
	
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
	huffman_build_tree(tree, inputStream);
	
	printf("%d\n", (int) tree->weight);

//	dynamic_array *volgorde_codes = da_create();
//
//	/** Boom opbouwen */
//	huffman_node *tree = malloc(sizeof(huffman_node));
//	int bitsread = build_tree(tree, "\0", volgorde_codes);
//
//	/* Padding */
//	while (bitsread % 8 != 0) {
//		getchar();
//		bitsread++;
//	}
//
//	/** Codes lezen en mappen. */
//	size_t amtcodes = volgorde_codes->size;
//	for (int i = 0; i < amtcodes; ++i) {
//		char *code = da_get(volgorde_codes, (size_t) i);
//		huffman_node *cursor = tree;
//		for(int j = 0; j < strlen(code); ++j) {
//			if(code[j] == '1') {
//				cursor = cursor->right;
//			} else {
//				cursor = cursor->left;
//			}
//		}
//		cursor->value = getchar();
//	}
//
//	int c;
//	huffman_node *cursor = tree;
//
//	while ((c = getchar()) > -1) {
//		char ch = (char) c;
//
//		if (ch == '1') {
//			cursor = cursor->right;
//		} else {
//			cursor = cursor->left;
//		}
//
//		if (cursor->type == LEAF) {
//			printf("%c", (char) cursor->value);
//			cursor = tree;
//		}
//	}
	
	byos_free(outputStream);
	bis_free(inputStream);
}
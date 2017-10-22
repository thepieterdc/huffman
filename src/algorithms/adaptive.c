/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"
#include "../datastructures/huffman_tree/huffman_tree.h"
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../util/logging.h"
#include "util/adaptive.h"

void huffman_adaptive_compress(FILE *input, FILE *output) {
	/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input);
	byis_consume(inputStream);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Create an empty Huffman tree. */
	huffman_tree *tree = huffmantree_create_empty();
	tree->root = tree->nyt;
	
	byte z;
	while (!byis_empty(inputStream)) {
		huffmantree_print(tree);
		
		z = byis_read(inputStream);
		printf("Read: %c", z);
		
		huffman_node *t;
		
		if (tree->leaves[z]) {
			printf(" -- Already in tree.\n");
			/* An existing character has been read. */
			t = tree->leaves[z];
		} else {
			printf(" -- New character.\n");
			/* A new character has been read. */
			huffman_node *o = add_character(tree, z);
			if (o->parent) {
				t = o->parent;
			} else {
				continue;
			}
		}
	}
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	info("Huffman adaptive decompress");
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"
#include "../util/logging.h"
#include "../datastructures/huffman_tree.h"
#include "../util/errors.h"
#include "util/adaptive.h"

#define NYT_INDEX 256

void huffman_adaptive_compress(FILE *input, FILE *output) {
	/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input);
	byis_consume(inputStream);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Create a Huffman tree, only containing the NYT node. */
	huffman_node *tree = create_nyt_tree();
	huffman_node *nyt = tree;
	
	huffman_node *nodes[257] = {};
	nodes[NYT_INDEX] = nyt;
	
	byte z;
	while (!byis_empty(inputStream)) {
		huffman_print_tree(tree);
		
		z = byis_read(inputStream);
		printf("Read: %c\n", z);
		
		huffman_node *t;
		
		if (nodes[z] != NULL) {
			/* an existing character has been read. */
			t = nodes[z];
		} else {
			/* a new character has been read. */
			huffman_node *o = add_character(&tree, nyt, z);
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
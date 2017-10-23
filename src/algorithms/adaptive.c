/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"
#include "util/adaptive.h"
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../util/logging.h"

void huffman_adaptive_compress(FILE *input, FILE *output) {
	/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input);
	byis_consume(inputStream);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Create an empty Huffman tree. */
	huffman_tree *tree = huffmantree_create_empty();
	tree->root = tree->nyt;
	
	/* Transform it into an Adaptive Huffman tree. */
	adaptive_huffman_tree aht;
	adaptivehuffmantree(&aht, tree);
	
	byte z;
	while (!byis_empty(inputStream)) {
		huffmantree_print(tree);
		
		z = byis_read(inputStream);
		printf("Read: %c\n", z);

		huffman_node *t;

		if (tree->leaves[z]) {
			/* An existing character has been read. */
			t = tree->leaves[z];
		} else {
			/* A new character has been read. */
			huffman_node *o = add_character(&aht, z);
			if (o->parent) {
				t = o->parent;
			} else {
				continue;
			}
		}

		while (t->parent) {
			huffman_node *tbar = find_tbar(&aht, t);
			if(tbar != t->parent) {
				aht_swap_nodes(&aht, t, tbar);
			}
			break;
		}
	}
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	info("Huffman adaptive decompress");
}
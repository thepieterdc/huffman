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
	byte_input_stream *inputStream = byis_create(input, false);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Encode the input. */
	byte z;
	while (inputStream->cursor <= inputStream->buffer_size - 2) {
		z = byis_read(inputStream);
		
		huffman_node *t = aht->tree->leaves[z];
		if (!t) {
			/* z is a new character; add it to the tree. */
			huffman_node *o = add_character(aht, z);
			t = o->parent;
		}
		
		/* Update the tree accordingly. */
		huffman_node *swap_node;
		while (t) {
			swap_node = aht->nodes[find_swap(aht, t->weight)];
			if (t != swap_node && swap_node->parent != t && t != swap_node->parent) {
				/* Swap the nodes in the tree. */
				do_swap(aht, t, swap_node);
			}
			t->weight++;
			t = t->parent;
		}
	}
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	info("Huffman adaptive decompress");
}
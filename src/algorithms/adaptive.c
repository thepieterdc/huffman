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
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Encode the input. */
	byte z;
	while (!byis_empty(inputStream)) {
		z = byis_read(inputStream);
		
		huffman_node *t = aht->tree->leaves[z];
		if (t == NULL) {
			huffman_node *o = add_character(aht, z);
			t = o->parent;
		}
		
		if (t != NULL) {
			update_tree(aht, t);
		}
		
		huffmantree_print(aht->tree);
	}
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	info("Huffman adaptive decompress");
}
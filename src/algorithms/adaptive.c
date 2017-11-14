/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "util/adaptive.h"
#include "util/common.h"
#include "sliding.h"

void huffman_adaptive_compress(FILE *input, FILE *output) {
	__huffman_sliding_compress(input, output, 0);
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Decode the input. */
	while (inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
		/* Output the decoded character. */
		huffman_node *t = adaptive_decode_character(aht, inputStream, output);
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
	}
	
	/* Decode the remaining bytes. */
	size_t indicator = huffman_finalize_input(inputStream);
	while(inputStream->current_cursor < indicator) {
		huffman_node *t = adaptive_decode_character(aht, inputStream, output);
		adaptive_update_tree(aht, t);
	}
	
	/* Flush the output buffer. */
	fflush(output);
	
	/* Cleanup allocated memory. */
	adaptivehuffmantree_free(aht);
	bis_free(inputStream);
}
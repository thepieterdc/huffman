/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "adaptive.h"
#include "util/adaptive.h"

void huffman_adaptive_compress(FILE *input, FILE *output) {
	/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input, false);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Encode the input. */
	byte z = byis_read(inputStream);
	while (inputStream->cursor <= inputStream->buffer_size) {
		/* Output the encoded character. */
		huffman_node *t = adaptive_encode_character(aht, z, outputStream);
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
		
		z = byis_read(inputStream);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	adaptivehuffmantree_free(aht);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_adaptive_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Create a buffer to store the output. */
	byte_output_stream *outputStream = byos_create(output);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Decode the input. */
	while (inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
		/* Output the decoded character. */
		huffman_node *t = adaptive_decode_character(aht, inputStream, outputStream);
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
	}
	
	/* Flush the output buffer. */
	byos_flush(outputStream);
	
	/* Cleanup allocated memory. */
	adaptivehuffmantree_free(aht);
	byos_free(outputStream);
	bis_free(inputStream);
}
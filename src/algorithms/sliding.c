/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "sliding.h"
#include "util/adaptive.h"
#include "util/sliding.h"
#include "../util/logging.h"
#include "../datastructures/byte_queue.h"

void huffman_sliding_compress(FILE *input, FILE *output) {
/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input, false);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Create a byte_queue to store the characters order. */
	byte_queue *window = byte_queue_create();
	
	/* Encode the input. */
	byte z = byis_read(inputStream);
	while (inputStream->cursor <= inputStream->buffer_size) {
		byte_queue_push(window, z);
		
		/* Output the encoded character. */
		huffman_node *t = adaptive_encode_character(aht, z, outputStream);
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
		
		/* Update the tree using the sliding window. */
		if (window->size > HUFFMAN_SLIDING_WINDOWSIZE) {
			sliding_update_tree(aht, byte_queue_pop(window));
		}
		
		z = byis_read(inputStream);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	byte_queue_free(window);
	adaptivehuffmantree_free(aht);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_sliding_decompress(FILE *input, FILE *output) {
	info("Huffman Sliding (decode)");
}
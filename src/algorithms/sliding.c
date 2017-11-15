/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "sliding.h"
#include "util/adaptive.h"
#include "util/sliding.h"
#include "util/common.h"

#define HUFFMAN_SLIDING_WINDOWSIZE 5

void __huffman_sliding_compress(FILE *input, FILE *output, size_t window_size) {
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
		if(window_size > 0) {
			byte_queue_push(window, z);
		}
		
		/* Output the encoded character. */
		huffman_node *t = adaptive_encode_character(aht, z, outputStream);
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
		
		/* Update the tree using the sliding window. */
		if (window->size > window_size) {
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

void huffman_sliding_compress(FILE *input, FILE *output) {
	__huffman_sliding_compress(input, output, HUFFMAN_SLIDING_WINDOWSIZE);
}

void __huffman_sliding_decompress(FILE *input, FILE *output, size_t window_size) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Create a byte_queue to store the characters order. */
	byte_queue *window = byte_queue_create();
	
	/* Decode the input. */
	while (inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
		/* Output the decoded character and append it to the window. */
		huffman_node *t;
		if(window_size) {
			t = sliding_decode_character(aht, window, inputStream, output);
		} else {
			t = adaptive_decode_character(aht, inputStream, output);
		}
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
		
		/* Update the tree using the sliding window. */
		if (window->size > window_size) {
			sliding_update_tree(aht, byte_queue_pop(window));
		}
	}
	
	/* Decode the remaining bytes. */
	size_t indicator = huffman_finalize_input(inputStream);
	while(inputStream->current_cursor < indicator) {
		huffman_node *t;
		if(window_size) {
			t = sliding_decode_character(aht, window, inputStream, output);
		} else {
			t = adaptive_decode_character(aht, inputStream, output);
		}
		adaptive_update_tree(aht, t);
		if (window->size > window_size) {
			sliding_update_tree(aht, byte_queue_pop(window));
		}
	}
	
	/* Flush the output buffer. */
	fflush(output);
	
	/* Cleanup allocated memory. */
	byte_queue_free(window);
	adaptivehuffmantree_free(aht);
	bis_free(inputStream);
}

void huffman_sliding_decompress(FILE *input, FILE *output) {
	__huffman_sliding_decompress(input, output, HUFFMAN_SLIDING_WINDOWSIZE);
}
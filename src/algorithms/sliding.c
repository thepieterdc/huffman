/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include "sliding.h"
#include "util/adaptive.h"
#include "util/sliding.h"
#include "util/common.h"

#define HUFFMAN_SLIDING_WINDOWSIZE 3

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
	size_t padding = BITS_IN_BYTE - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	putc_unlocked((byte) padding, output);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	byte_queue_free(window);
	adaptivehuffmantree_free(aht);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_sliding_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Prepare the output channel. */
	huffman_prepare_output(output);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht = adaptivehuffmantree_create();
	
	/* Create a byte_queue to store the characters order. */
	byte_queue *window = byte_queue_create();
	
	/* Decode the input. */
	while (inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
		/* Output the decoded character and append it to the window. */
		huffman_node *t = sliding_decode_character(aht, window, inputStream, output);
		
		/* Update the tree accordingly. */
		adaptive_update_tree(aht, t);
		
		/* Update the tree using the sliding window. */
		if (window->size > HUFFMAN_SLIDING_WINDOWSIZE) {
			sliding_update_tree(aht, byte_queue_pop(window));
		}
	}
	
	/* Decode the remaining byte. */
	size_t indicator = huffman_finalize_input(inputStream);
	while(inputStream->current_cursor < indicator) {
		huffman_node *t = sliding_decode_character(aht, window, inputStream, output);
		
		adaptive_update_tree(aht, t);
		
		if (window->size > HUFFMAN_SLIDING_WINDOWSIZE) {
			sliding_update_tree(aht, byte_queue_pop(window));
		}
	}
	
	/* Flush the output buffer. */
	fflush(output);
	funlockfile(output);
	
	/* Cleanup allocated memory. */
	byte_queue_free(window);
	adaptivehuffmantree_free(aht);
	bis_free(inputStream);
}
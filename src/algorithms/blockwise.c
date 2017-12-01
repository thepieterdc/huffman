/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include "blockwise.h"
#include "../util/logging.h"
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "util/adaptive.h"
#include "util/common.h"

#define HUFFMAN_BLOCKWISE_BLOCKSIZE 1024

void huffman_blockwise_compress(FILE *input, FILE *output) {
	/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input, false);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	adaptive_huffman_tree *aht;
	byte z = byis_read(inputStream);
	size_t blocksize;
	while(true) {
		blocksize = 0;
		
		/* Create an Adaptive Huffman tree. */
		aht = adaptivehuffmantree_create();
		
		/* Encode the input. */
		while (blocksize++ < HUFFMAN_BLOCKWISE_BLOCKSIZE && inputStream->cursor <= inputStream->buffer_size) {
			/* Output the encoded character. */
			huffman_node *t = adaptive_encode_character(aht, z, outputStream);
			
			/* Update the tree accordingly. */
			adaptive_update_tree(aht, t);
			
			z = byis_read(inputStream);
		}
		
		/* Release allocated memory. */
		adaptivehuffmantree_free(aht);
		
		if(inputStream->cursor > inputStream->buffer_size) {
			break;
		}
	}
	
	/* Apply padding after the last bits. */
	size_t padding = BITS_IN_BYTE - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	putc_unlocked((byte) padding, output);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_blockwise_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Prepare the output channel. */
	huffman_prepare_output(output);
	
	/* Create an Adaptive Huffman tree. */
	adaptive_huffman_tree *aht;
	size_t blocksize;
	while(true) {
		blocksize = 0;
		
		aht = adaptivehuffmantree_create();
		
		/* Decode the input. */
		while (blocksize++ < HUFFMAN_BLOCKWISE_BLOCKSIZE && inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
			/* Output the decoded character and append it to the window. */
			huffman_node *t = adaptive_decode_character(aht, inputStream, output);
			
			/* Update the tree accordingly. */
			adaptive_update_tree(aht, t);
		}
		
		if(inputStream->stream->cursor > inputStream->stream->buffer_size - 2) {
			break;
		}
		
		/* Release allocated memory. */
		adaptivehuffmantree_free(aht);
	}
	
	/* Decode the remaining byte. */
	size_t indicator = huffman_finalize_input(inputStream);
	while(inputStream->current_cursor < indicator) {
		huffman_node *t = adaptive_decode_character(aht, inputStream, output);
		adaptive_update_tree(aht, t);
	}
	
	/* Flush the output buffer. */
	fflush(output);
	funlockfile(output);
	
	/* Cleanup allocated memory. */
	adaptivehuffmantree_free(aht);
	bis_free(inputStream);
}
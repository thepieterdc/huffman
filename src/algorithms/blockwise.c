/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "blockwise.h"
#include "../util/logging.h"
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "util/adaptive.h"

#define HUFFMAN_BLOCKWISE_BLOCKSIZE 3

void huffman_blockwise_compress(FILE *input, FILE *output) {
	/* Create a stream to process the input. */
	byte_input_stream *inputStream = byis_create(input, false);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	adaptive_huffman_tree *aht;
	byte z;
	size_t blocksize = 0;
	while(true) {
		/* Create an Adaptive Huffman tree. */
		aht = adaptivehuffmantree_create();
		
		/* Encode the input. */
		z = byis_read(inputStream);
		while (inputStream->cursor <= inputStream->buffer_size) {
			/* Output the encoded character. */
			huffman_node *t = adaptive_encode_character(aht, z, outputStream);
			
			/* Update the tree accordingly. */
			adaptive_update_tree(aht, t);
			
			if(++blocksize >= HUFFMAN_BLOCKWISE_BLOCKSIZE) {
				break;
			}
			
			z = byis_read(inputStream);
		}
		
		/* Release allocated memory. */
		adaptivehuffmantree_free(aht);
		
		if(blocksize < HUFFMAN_BLOCKWISE_BLOCKSIZE) {
			break;
		}
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_blockwise_decompress(FILE *input, FILE *output) {
	info("Blockwise decompress");
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "twopass.h"
#include "../util/logging.h"
#include "../io/input/byte_input_stream.h"
#include "../io/output/bit_output_stream.h"
#include "../util/errors.h"
#include "../datastructures/huffman_tree/huffman_tree.h"
#include "util/standard.h"
#include "util/twopass.h"
#include "util/adaptive.h"
#include "util/sliding.h"
#include "util/common.h"

void huffman_twopass_compress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	byte_input_stream *inputStream = byis_create(input, true);
	
	/* Create a buffer to store the output. */
	bit_output_stream *outputStream = bos_create(output);
	
	/* Determine the frequencies of each character. */
	uint_least32_t frequencies[256] = {0};
	
	while (inputStream->cursor <= inputStream->buffer_size) {
		frequencies[byis_read(inputStream)]++;
	}
	
	/* Failsafe for empty input. */
	if (inputStream->buffer_size == 0) {
		error(ERROR_END_OF_INPUT);
	}
	
	/* Create a new Adaptive Huffman tree. */
	adaptive_huffman_tree aht;
	huffman_tree *tree = standard_build_tree_from_frequencies(frequencies);
	
	/* Print the Huffman tree and apply padding. */
	standard_print_tree(tree->root, outputStream);
	bos_pad(outputStream);
	
	/* Print the characters from left to right. */
	standard_print_characters(tree->root, outputStream);
	
	/* Print the weights from left to right. */
	twopass_print_weights(tree->root, outputStream);
	
	/* Convert the tree into an Adaptive Huffman tree. */
	twopass_parse_tree(&aht, tree);
	
	/* Rewind the input. */
	inputStream->cursor = 0;
	
	/* Encode the input. */
	byte z = byis_read_dirty(inputStream);
	while (inputStream->cursor <= inputStream->buffer_size) {
		/* Output the encoded character. */
		adaptive_print_code(tree->leaves[z], outputStream);
		
		/* Update the tree, don't update if there is only 1 character leaf left. */
		if (aht.amt_nodes > 2) {
			sliding_update_tree(&aht, z);
		}
		
		z = byis_read_dirty(inputStream);
	}
	
	/* Apply padding after the last bits. */
	size_t padding = 8 - bos_pad(outputStream);
	
	/* Output the amount of padding bits added. */
	bos_feed_byte(outputStream, (byte) padding);
	
	/* Flush the output buffer. */
	bos_flush(outputStream);
	
	/* Release allocated memory. */
	huffmantree_free(tree);
	bos_free(outputStream);
	byis_free(inputStream);
}

void huffman_twopass_decompress(FILE *input, FILE *output) {
	/* Create a buffer to store the input. */
	bit_input_stream *inputStream = bis_create(input, false);
	
	/* Prepare the output channel. */
	huffman_prepare_output(output);
	
	/* Build up the Huffman tree. */
	huffman_tree *tree = huffmantree_create(NULL);
	tree->root->code = huffmancode_create();
	
	/* Create a new Adaptive Huffman tree. */
	adaptive_huffman_tree aht;
	standard_build_tree_from_bits(tree->root, inputStream, false);
	
	/* Clear the remaining padding bits. */
	bis_clear_current_byte(inputStream);
	
	/* Assign characters to leaves. */
	standard_assign_characters(tree, inputStream);
	
	/* Assign weights to leaves. */
	twopass_assign_weights(tree->root, inputStream);
	
	/* Convert the tree into an Adaptive Huffman tree. */
	twopass_parse_tree(&aht, tree);
	
	/* Decode the input. */
	byte z;
	while (inputStream->stream->cursor <= inputStream->stream->buffer_size - 2) {
		/* Output the decoded character. */
		z = twopass_decode_character(tree, inputStream, output);
		
		/* Update the tree, don't update if there is only 1 character leaf left. */
		if (aht.amt_nodes > 2) {
			sliding_update_tree(&aht, z);
		}
	}
	
	/* Decode the remaining bytes. */
	size_t indicator = huffman_finalize_input(inputStream);
	while (inputStream->current_cursor < indicator) {
		/* Output the decoded character. */
		z = twopass_decode_character(tree, inputStream, output);
		
		/* Update the tree, don't update if there is only 1 character leaf left. */
		if (aht.amt_nodes > 2) {
			sliding_update_tree(&aht, z);
		}
	}
	
	/* Flush the output buffer. */
	fflush(output);
	funlockfile(output);
	
	/* Cleanup allocated memory. */
	huffmantree_free(tree);
	bis_free(inputStream);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "standard.h"
#include "../../io/input/bit_input_stream.h"
#include "../../util/logging.h"

void assign_characters(huffman_node *root, bit_input_stream *in) {
	if (root->type == LEAF) {
		root->data = bis_read_byte(in);
	} else {
		assign_characters(root->left, in);
		assign_characters(root->right, in);
	}
}

void build_dictionary(huffman_node *root, huffman_code *code, huffman_code **dictionary, bit_output_stream *out) {
	if (root->type == LEAF) {
		root->code = code;
		dictionary[root->data] = code;
		bos_feed_byte(out, root->data);
	} else {
		huffman_code *leftcode = huffmancode_create_left(code);
		build_dictionary(root->left, leftcode, dictionary, out);
		huffman_code *rightcode = huffmancode_create_right(code);
		build_dictionary(root->right, rightcode, dictionary, out);
		huffmancode_free(code);
	}
}

void build_tree(huffman_node *root, bit_input_stream *input) {
	bit rd = bis_read_bit(input);
	root->type = rd ? LEAF : NODE;
	if (!rd) {
		root->left = huffman_create_node(NULL, NULL);
		root->left->code = huffmancode_create_left(root->code);
		build_tree(root->left, input);
		
		root->right = huffman_create_node(NULL, NULL);
		root->right->code = huffmancode_create_right(root->code);
		build_tree(root->right, input);
	}
}

byte decode_character(huffman_node *tree, bit_input_stream *in) {
	huffman_node *cursor = tree;
	while (cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	return cursor->data;
}

void decode_final_byte(huffman_node *tree, byte_output_stream *out, byte b, size_t amount) {
	while (amount > 0) {
		huffman_node *cursor = tree;
		while (cursor->type != LEAF) {
			bit rd = (bit) (b & (1 << 7));
			cursor = rd ? cursor->right : cursor->left;
			b <<= 1;
			--amount;
		}
		byos_feed(out, cursor->data);
	}
}

void print_tree(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		bos_feed_bit(out, 1);
	} else {
		bos_feed_bit(out, 0);
		
		print_tree(root->left, out);
		print_tree(root->right, out);
	}
}
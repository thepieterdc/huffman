/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "standard.h"

void standard_assign_characters(huffman_node *root, bit_input_stream *in) {
	if (root->type == LEAF) {
		root->data = bis_read_byte(in);
	} else {
		standard_assign_characters(root->left, in);
		standard_assign_characters(root->right, in);
	}
}

void standard_build_tree(huffman_node *root, bit_input_stream *input) {
	bit rd = bis_read_bit(input);
	root->type = rd ? LEAF : NODE;
	if (!rd) {
		root->left = huffmannode_create_node(NULL, NULL);
		root->left->code = huffmancode_create_left(root->code);
		standard_build_tree(root->left, input);
		
		root->right = huffmannode_create_node(NULL, NULL);
		root->right->code = huffmancode_create_right(root->code);
		standard_build_tree(root->right, input);
	}
}

byte standard_decode_character(huffman_node *tree, bit_input_stream *in) {
	huffman_node *cursor = tree;
	while (cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	return cursor->data;
}

void standard_decode_final_byte(huffman_node *tree, byte_output_stream *out, byte b, size_t amount) {
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

void standard_print_characters(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		bos_feed_byte(out, root->data);
	} else {
		standard_print_characters(root->left, out);
		standard_print_characters(root->right, out);
	}
}

void standard_print_tree(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		bos_feed_bit(out, 1);
	} else {
		bos_feed_bit(out, 0);
		
		standard_print_tree(root->left, out);
		standard_print_tree(root->right, out);
	}
}
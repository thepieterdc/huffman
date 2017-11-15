/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "standard.h"
#include "../../datastructures/huffman_tree/huffman_tree.h"
#include "../../datastructures/min_heap.h"

void standard_assign_characters(huffman_node *root, bit_input_stream *in) {
	if (root->type == LEAF) {
		root->data = bis_read_byte(in);
	} else {
		standard_assign_characters(root->left, in);
		standard_assign_characters(root->right, in);
	}
}

void standard_build_tree_from_bits(huffman_node *root, bit_input_stream *input) {
	bit rd = bis_read_bit(input);
	root->type = rd ? LEAF : NODE;
	if (!rd) {
		root->left = huffmannode_create_node(NULL, NULL);
		root->left->code = huffmancode_create_left(root->code);
		standard_build_tree_from_bits(root->left, input);
		
		root->right = huffmannode_create_node(NULL, NULL);
		root->right->code = huffmancode_create_right(root->code);
		standard_build_tree_from_bits(root->right, input);
	}
}

huffman_tree *standard_build_tree_from_frequencies(uint_least64_t frequencies[]) {
	huffman_tree *tree = huffmantree_create_empty();
	
	/* Add all bytes to a heap. */
	min_heap *heap = minheap_create(256);
	for (size_t i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			huffman_node *leaf = huffmannode_create_leaf((byte) i, frequencies[i]);
			tree->leaves[i] = leaf;
			minheap_insert(heap, leaf->weight, leaf);
		}
	}
	
	/* Failsafe for strings containing 1 character. */
	if (heap->size == 1) {
		huffman_node *nullnode = huffmannode_create_leaf(0, 1);
		minheap_insert(heap, nullnode->weight, nullnode);
	}
	
	/* Fill the Huffman tree. */
	while (heap->size > 1) {
		huffman_node *left = minheap_extract_min(heap);
		huffman_node *right = minheap_extract_min(heap);
		huffman_node *parent = huffmannode_create_node(left, right);
		minheap_insert(heap, parent->weight, parent);
	}
	
	tree->root = minheap_find_min(heap);
	
	minheap_free(heap);
	
	return tree;
}

byte standard_decode_character(huffman_node *tree, bit_input_stream *in) {
	huffman_node *cursor = tree;
	while (cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	return cursor->data;
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
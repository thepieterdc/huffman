/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <stdlib.h>
#include "adaptive.h"

huffman_node *add_character(adaptive_huffman_tree *tree, byte data) {
	huffman_node *parent = tree->nyt->parent;
	huffman_node *newleaf = huffmannode_create_leaf(data, 1);
	newleaf->order_no = (uint_least16_t) (tree->amt_nodes + 1);
	tree->tree->leaves[data] = newleaf;
	
	huffman_node *ret = huffmannode_create_node(tree->nyt, newleaf);
	ret->order_no = tree->amt_nodes;
	ret->parent = parent;
	
	
	if (parent) {
		parent->left = ret;
	} else {
		tree->tree->root = ret;
	}
	
	tree->nodes[ret->order_no] = ret;
	tree->nodes[newleaf->order_no] = newleaf;
	
	tree->amt_nodes += 2;
	
	return ret;
}

void do_swap(adaptive_huffman_tree *tree, huffman_node *node1, huffman_node *node2) {
	tree->nodes[node1->order_no] = node2;
	tree->nodes[node2->order_no] = node1;
	
	huffman_node *temp = node1->parent;
	node1->parent = node2->parent;
	node2->parent = temp;
	
	uint_least16_t temp_o = node1->order_no;
	node1->order_no = node2->order_no;
	node2->order_no = temp_o;
	
	if (node1->parent->left == node2) {
		node1->parent->left = node1;
	} else {
		node1->parent->right = node1;
	}
	
	if (node2->parent->left == node1) {
		node2->parent->left = node2;
	} else {
		node2->parent->right = node2;
	}
}

huffman_node *encode_character(adaptive_huffman_tree *tree, byte character, bit_output_stream *out) {
	if (tree->amt_nodes == 0) {
		bos_feed_byte(out, character);
		return NULL;
	}
	
	huffman_node *ret = tree->tree->leaves[character];
	if (!ret) {
		print_code(tree, tree->nyt, out);
//		bos_feed_byte(out, character);
	} else {
//		print_code(ret, out);
	}
	
	return ret;
}

uint_least16_t find_swap(adaptive_huffman_tree *tree, uint_least64_t weight) {
	for (uint_least16_t i = 0; i < tree->amt_nodes; ++i) {
		if (tree->nodes[i]->weight == weight) {
			return i;
		}
	}
	return 0;
}

void print_code(adaptive_huffman_tree *tree, huffman_node *node, bit_output_stream *out) {
	bit code[HUFFMAN_MAX_CODE_LENGTH];
	size_t codelength = 0;
	
	huffman_node *cursor = node;
	size_t len = 0;

	while (cursor->parent != NULL) {
//		code[codelength++] = cursor->parent->left != cursor;
		cursor = cursor->parent;
		len++;
		
		if(len == 256) {
			huffmantree_print(tree->tree);
			exit(10);
		}
	}
//	for (size_t i = codelength; i > 0; --i) {
//		bos_feed_bit(out, code[i - 1]);
//	}
}
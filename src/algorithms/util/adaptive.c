/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"

huffman_node *add_character(huffman_node **tree, huffman_node *nyt, byte data) {
	huffman_node *newleaf = huffman_create_leaf(data, 1);
	newleaf->order_no = 1;
	
	huffman_node *ret;
	
	huffman_node *parent = nyt->parent;
	if (parent != NULL) {
		increment_ordernumbers(*tree, 2);
		
		ret = huffman_create_node(nyt, newleaf);
		parent->left = ret;
	} else {
		ret = huffman_create_node(nyt, newleaf);
		*tree = ret;
	}
	
	ret->order_no = 2;
	ret->weight = 1;
	
	return ret;
}

huffman_node *create_nyt_tree() {
	huffman_node *nyt = huffman_create_node(NULL, NULL);
	nyt->code = huffmancode_create();
	nyt->order_no = 0;
	nyt->weight = 0;
	return nyt;
}

void increment_ordernumbers(huffman_node *tree, size_t amount) {
	if (tree->weight != 0) {
		/* Don't update the NYT node. */
		tree->order_no += amount;
	}
	
	if (tree->left != NULL) {
		increment_ordernumbers(tree->left, amount);
	}
	
	if (tree->right != NULL) {
		increment_ordernumbers(tree->right, amount);
	}
}
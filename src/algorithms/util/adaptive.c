/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"

huffman_node *add_character(huffman_tree *tree, byte data) {
	huffman_node *parent = tree->nyt->parent;
	huffman_node *ret = huffmannode_create_node(tree->nyt, NULL);
	ret->weight = 1;
	
	huffman_node *newleaf = huffmannode_create_leaf(data, 1);
	tree->leaves[data] = newleaf;
	ret->right = newleaf;
	
	if (parent) {
		parent->left = ret;
	} else {
		tree->root = ret;
	}
	
	return ret;
}

huffman_node *find_tbar(adaptive_huffman_tree *tree, huffman_node *t) {
	for (size_t i = tree->amt_nodes; i > 0; --i) {
		if (tree->nodes[i]->weight == t->weight) {
			return tree->nodes[i];
		}
	}
	return NULL;
}
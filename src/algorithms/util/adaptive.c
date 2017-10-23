/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"

huffman_node *add_character(adaptive_huffman_tree *tree, byte data) {
	huffman_node *parent = tree->tree->nyt->parent;
	huffman_node *ret = huffmannode_create_node(tree->tree->nyt, NULL);
	ret->weight = 1;
	
	huffman_node *newleaf = huffmannode_create_leaf(data, 1);
	tree->tree->leaves[data] = newleaf;
	ret->right = newleaf;
	newleaf->parent = ret;
	
	if (parent) {
		parent->left = ret;
		ret->parent = parent;
	} else {
		tree->tree->root = ret;
	}
	
	tree->nodes[tree->amt_nodes++] = ret;
	tree->nodes[tree->amt_nodes++] = newleaf;
	
	return ret;
}

huffman_node *find_tbar(adaptive_huffman_tree *tree, huffman_node *t) {
	for (size_t i = 0; i < tree->amt_nodes; ++i) {
		if (tree->nodes[i]->weight == t->weight) {
			return tree->nodes[i];
		}
	}
	return NULL;
}
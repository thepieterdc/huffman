/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "adaptive.h"

huffman_node *add_character(huffman_tree *tree, byte data) {
	huffman_node *ret;
	
	huffman_node *newleaf = huffmannode_create_leaf(data, 1);
	tree->leaves[data] = newleaf;
	
	huffman_node *parent = tree->nyt->parent;
	ret = huffmannode_create_node(tree->nyt, newleaf);
	if (parent) {
		parent->left = ret;
	} else {
		huffmantree_set_root(tree, ret);
	}
	
	return ret;
}
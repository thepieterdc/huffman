/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "sliding.h"

void sliding_decrease_character(adaptive_huffman_tree *tree, byte b) {
	huffman_node *node = tree->tree->leaves[b];
	
	if (!ret) {
		/* z is a new character; add it to the tree. */
		huffman_node *o = adaptive_add_character(tree, character);
		ret = o->parent;
	}
	
	return ret;
}
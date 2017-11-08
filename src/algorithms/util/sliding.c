/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "sliding.h"
#include "../../util/logging.h"
#include "adaptive.h"

uint_least16_t sliding_find_swap(adaptive_huffman_tree *tree, uint_least64_t weight) {
	for (uint_least16_t i = tree->amt_nodes; i > 0; --i) {
		if (tree->nodes[i - 1]->weight == weight) {
			return (uint_least16_t) (i - 1);
		}
	}
	return 0;
}

void sliding_update_tree(adaptive_huffman_tree *tree, byte b) {
	huffman_node *t = tree->tree->leaves[b];
	huffman_node *swap_node;
	
	/* Remove the node from the tree. */
	bool remove = t->weight == 1;
	
	while (t->parent) {
		swap_node = tree->nodes[sliding_find_swap(tree, t->weight)];
		if (t != swap_node && swap_node->parent != t && t->parent != swap_node) {
			/* Swap the nodes in the tree. */
			adaptive_do_swap(tree, t, swap_node);
		}
		t->weight--;
		t = t->parent;
	}
	t->weight--;
	
	if (remove) {
		huffmantree_print(tree->tree);
		
		huffman_node *parent = tree->nyt->parent;
		huffman_node *remove_node = parent->right;
		
		tree->nyt->parent = parent->parent;
		if (parent->parent->left == parent) {
			parent->parent->left = tree->nyt;
		} else {
			parent->parent->right = tree->nyt;
		}
		
		parent->left = NULL;
		parent->right = NULL;
		
		huffmannode_free(parent);
		huffmannode_free(remove_node);
		
		tree->amt_nodes -= 2;
		
		huffmantree_print(tree->tree);
	}
}
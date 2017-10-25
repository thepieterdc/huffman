/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "adaptive.h"

huffman_node *add_character(adaptive_huffman_tree *tree, byte data) {
	huffman_node *parent = tree->nyt->parent;
	huffman_node *ret = huffmannode_create_node(tree->nyt, NULL);
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

/**
 * Swaps 2 nodes in the Adaptive Huffman tree.
 *
 * @param tree the Adaptive Huffman tree
 * @param node1 the first node
 * @param node2 the second node
 */
static void do_swap(adaptive_huffman_tree *tree, huffman_node *node1, huffman_node *node2) {
	huffman_node temp = *node1;
	*node1 = *node2;
	*node2 = temp;
	tree->nodes[node1->order_no] = node1;
	tree->nodes[node2->order_no] = node2;
}

/**
 * Finds the node t' to swap with.
 *
 * @param tree the Adaptive Huffman tree
 * @param weight the weight of the node t
 */
static huffman_node *find_swap(adaptive_huffman_tree *tree, uint_least64_t weight) {
	for (size_t i = 0; i < tree->amt_nodes; ++i) {
		if (tree->nodes[i]->weight == weight) {
			return tree->nodes[i];
		}
	}
	return NULL;
}

void update_tree(adaptive_huffman_tree *tree, huffman_node *t) {
	huffman_node *swap_node;
	huffman_node *cursor = t;
	while (cursor->parent != NULL) {
		swap_node = find_swap(tree, cursor->weight);
		if (cursor->parent != swap_node) {
			do_swap(tree, cursor, swap_node);
		}
		cursor->weight++;
		cursor = cursor->parent;
	}
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "adaptive_huffman_tree.h"

/**
 * Recursive step to set the nodes in an Adaptive Huffman tree.
 *
 * @param aht the Adaptive Hufman tree
 * @param ht the current subtree root
 */
static void set_nodes(adaptive_huffman_tree *aht, huffman_node *ht) {
	aht->nodes[ht->order_no] = ht;
	if (ht->type != NYT) {
		aht->amt_nodes++;
	}
	
	if (ht->left && ht->right) {
		set_nodes(aht, ht->left);
		set_nodes(aht, ht->right);
	}
}

void adaptivehuffmantree(adaptive_huffman_tree *aht, huffman_tree *ht) {
	aht->tree = ht;
	aht->amt_nodes = 0;
	
	set_nodes(aht, ht->root);
}
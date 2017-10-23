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

void aht_swap_nodes(adaptive_huffman_tree *aht, huffman_node *node1, huffman_node *node2) {
	fprintf(stderr, "SWAPPING\n");
	huffmantree_print(aht->tree);
	huffman_node temp = *node1;
	*node1 = *node2;
	*node2 = temp;
	huffmantree_print(aht->tree);
}
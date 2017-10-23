/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_ADAPTIVEHUFFMANTREE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_ADAPTIVEHUFFMANTREE_H

#include "huffman_tree.h"

#define HUFFMAN_MAX_NODES 513

/**
 * An adaptive Huffman tree.
 */
typedef struct adaptive_huffman_tree {
	struct huffman_tree *tree;
	size_t amt_nodes;
	struct huffman_node *nodes[HUFFMAN_MAX_NODES];
} adaptive_huffman_tree;

/**
 * Initialises an Adaptive Huffman tree.
 *
 * @param aht the Adaptive Huffman tree
 * @param tree the encapsulated tree
 */
void adaptivehuffmantree(adaptive_huffman_tree *aht, huffman_tree *ht);

/**
 * Swaps 2 nodes in an Adaptive Huffman tree.
 *
 * @param aht the Adaptive Huffman tree
 * @param node1 the first node
 * @param node2 the second node
 */
void aht_swap_nodes(adaptive_huffman_tree *aht, huffman_node *node1, huffman_node *node2);

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_ADAPTIVEHUFFMANTREE_H */
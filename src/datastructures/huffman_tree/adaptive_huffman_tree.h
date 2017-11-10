/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_ADAPTIVEHUFFMANTREE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_ADAPTIVEHUFFMANTREE_H

#include "huffman_tree.h"

#define HUFFMAN_MAX_NODES 515

/**
 * An adaptive Huffman tree.
 */
typedef struct adaptive_huffman_tree {
	struct huffman_tree *tree;
	struct huffman_node *nyt;
	uint_least16_t amt_nodes;
	struct huffman_node *nodes[HUFFMAN_MAX_NODES];
} adaptive_huffman_tree;

/**
 * Creates an Adaptive Huffman tree.
 *
 * @return the created Adaptive Huffman tree
 */
adaptive_huffman_tree *adaptivehuffmantree_create();

/**
 * Frees the memory allocated by a given Adaptive Huffman tree.
 *
 * @param aht the Adaptive Huffman tree
 */
void adaptivehuffmantree_free(adaptive_huffman_tree *aht);

/**
 * Initialises an Adaptive Huffman tree.
 *
 * @param aht the Adaptive Huffman tree
 */
void adaptivehuffmantree_initialise(adaptive_huffman_tree *aht, huffman_tree *tree);

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_ADAPTIVEHUFFMANTREE_H */
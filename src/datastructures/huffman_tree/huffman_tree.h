/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANTREE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANTREE_H

#include "huffman_node.h"

#define HUFFMAN_MAX_LEAVES 256

/**
 * A Huffman tree.
 */
typedef struct huffman_tree {
	struct huffman_node *root;
	struct huffman_node *nyt;
	struct huffman_node *leaves[HUFFMAN_MAX_LEAVES];
} huffman_tree;

/**
 * Creates a new Huffman tree optionally given an existing root.
 *
 * @param root the root of the tree, will be created if null
 * @return the created Huffman tree
 */
huffman_tree *huffmantree_create(huffman_node *root);

/**
 * Creates an empty Huffman tree.
 *
 * @return the created Huffman tree
 */
huffman_tree *huffmantree_create_empty();

/**
 * Frees the memory allocated by a Huffman tree.
 *
 * @param tree the tree to free
 */
void huffmantree_free(huffman_tree *tree);

/**
 * Prints a Huffman tree to stderr for debugging purposes.
 *
 * @param tree the tree to print
 */
void huffmantree_print(huffman_tree *tree);

/**
 * Sets the codes in a Huffman tree.
 *
 * @param tree the tree
 */
void huffmantree_set_codes(huffman_tree *tree);

/**
 * Swaps 2 nodes in a Huffman tree.
 *
 * @param node1 the first node
 * @param node2 the second node
 */
void huffmantree_swap_nodes(huffman_node *node1, huffman_node *node2);

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANTREE_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H
#define HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H

#include "../../datastructures/huffman_tree/adaptive_huffman_tree.h"

/**
 * Creates a tree for a new character in the existing Huffman tree.
 *
 * @param tree the tree
 * @param data the data to add
 * @return the node having NYT and the new character as children
 */
huffman_node *add_character(adaptive_huffman_tree *tree, byte data);

/**
 * Finds t' for a given t.
 *
 * @param tree the Huffman tree
 * @param t the t-node
 * @return the t' node
 */
huffman_node *find_tbar(adaptive_huffman_tree *tree, huffman_node *t);

#endif /* HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H */

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
 * Swaps 2 nodes in the Adaptive Huffman tree.
 *
 * @param tree the Adaptive Huffman tree
 * @param node1 the first node
 * @param node2 the second node
 */
void do_swap(adaptive_huffman_tree *tree, huffman_node *node1, huffman_node *node2);

/**
 * Finds the node t' to swap with.
 *
 * @param tree the Adaptive Huffman tree
 * @param weight the weight of the node t
 * @return the ordernumber to swap with
 */
uint_least16_t find_swap(adaptive_huffman_tree *tree, uint_least64_t weight);

#endif /* HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H */

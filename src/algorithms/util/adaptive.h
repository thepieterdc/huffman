/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H
#define HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H

#include "../../datastructures/huffman_tree.h"

/**
 * Creates a tree for a new character in the existing Huffman tree.
 *
 * @param tree pointer to the exisiting tree
 * @param nyt the NYT node
 * @param data the data to add
 * @return the node having NYT and the new character as children
 */
huffman_node *add_character(huffman_node **tree, huffman_node *nyt, byte data);

/**
 * Creates a Huffman tree containing the NYT node.
 *
 * @return the created tree
 */
huffman_node *create_nyt_tree();

/**
 * Recursively increments all ordernumbers in a given tree.
 *
 * @param tree the Huffman tree to process
 * @param amount the amount to increment
 */
void increment_ordernumbers(huffman_node *tree, size_t amount);

#endif /* HUFFMAN_ALGORITHMS_UTIL_AAPTIVE_H */

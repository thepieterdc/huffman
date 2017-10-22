/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H
#define HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H

#include "../../datastructures/huffman_tree/huffman_tree.h"

/**
 * Creates a tree for a new character in the existing Huffman tree.
 *
 * @param tree the tree
 * @param data the data to add
 * @return the node having NYT and the new character as children
 */
huffman_node *add_character(huffman_tree *tree, byte data);

#endif /* HUFFMAN_ALGORITHMS_UTIL_AAPTIVE_H */
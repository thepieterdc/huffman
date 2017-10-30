/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H
#define HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H

#include "../../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "../../io/output/bit_output_stream.h"

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
 * Encodes a character and appends this to the output stream.
 *
 * @param tree the Adaptive Huffman tree
 * @param character the character to encode
 * @param out the output stream
 * @return the leaf containing this character, returns NULL for a new character
 */
huffman_node *encode_character(adaptive_huffman_tree *tree, byte character, bit_output_stream *out);

/**
 * Finds the node t' to swap with.
 *
 * @param tree the Adaptive Huffman tree
 * @param weight the weight of the node t
 * @return the ordernumber to swap with
 */
uint_least16_t find_swap(adaptive_huffman_tree *tree, uint_least64_t weight);

/**
 * Finds and outputs the Huffman code for a given node.
 *
 * @param node the node to find the code for
 * @param out the output stream
 */
void print_code(huffman_node *node, bit_output_stream *out);

#endif /* HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H */

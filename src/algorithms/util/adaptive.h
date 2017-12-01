/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H
#define HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include "../../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "../../io/output/bit_output_stream.h"
#include "../../io/input/bit_input_stream.h"

/**
 * Creates a tree for a new character in the existing Huffman tree.
 *
 * @param tree the tree
 * @param data the data to add
 * @return the node having NYT and the new character as children
 */
huffman_node *adaptive_add_character(adaptive_huffman_tree *tree, byte data);

/**
 * Decodes a character and appends this to the output stream. New characters
 * will be added to the tree.
 *
 * @param tree the Adaptive Huffman tree
 * @param in the input stream
 * @param out the output stream
 * @return the leaf containing this character
 */
huffman_node *adaptive_decode_character(adaptive_huffman_tree *tree, bit_input_stream *in, FILE *out);

/**
 * Swaps 2 nodes in the Adaptive Huffman tree.
 *
 * @param tree the Adaptive Huffman tree
 * @param node1 the first node
 * @param node2 the second node
 */
void adaptive_do_swap(adaptive_huffman_tree *tree, huffman_node *node1, huffman_node *node2);

/**
 * Encodes a character and appends this to the output stream. New characters
 * will be added to the tree.
 *
 * @param tree the Adaptive Huffman tree
 * @param character the character to encode
 * @param out the output stream
 * @return the leaf containing this character
 */
huffman_node *adaptive_encode_character(adaptive_huffman_tree *tree, byte character, bit_output_stream *out);

/**
 * Finds the node t' to swap with.
 *
 * @param tree the Adaptive Huffman tree
 * @param node the node t
 * @return the ordernumber to swap with
 */
uint_fast16_t adaptive_find_swap(adaptive_huffman_tree *tree, huffman_node *node);

/**
 * Finds and outputs the Huffman code for a given node.
 *
 * @param node the node to find the code for
 * @param out the output stream
 */
void adaptive_print_code(huffman_node *node, bit_output_stream *out);

/**
 * Updates the Adaptive Huffman tree.
 *
 * @param tree the Adaptive Huffman tree to update
 * @param t the start node
 */
void adaptive_update_tree(adaptive_huffman_tree *tree, huffman_node *t);

#endif /* HUFFMAN_ALGORITHMS_UTIL_ADAPTIVE_H */

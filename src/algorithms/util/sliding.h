/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_SLIDING_H
#define HUFFMAN_ALGORITHMS_UTIL_SLIDING_H

#include "../../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "../../io/output/bit_output_stream.h"
#include "../../io/input/bit_input_stream.h"

/**
 * Finds the node t' to swap with.
 *
 * @param tree the Adaptive Huffman tree
 * @param weight the weight of the node t
 * @return the ordernumber to swap with
 */
uint_least16_t sliding_find_swap(adaptive_huffman_tree *tree, uint_least64_t weight);

/**
 * Decreases a character in an Adaptive Huffman tree and updates the tree.
 *
 * @param tree the Adaptive Huffman tree
 * @param b the character to decrease
 */
void sliding_update_tree(adaptive_huffman_tree *tree, byte b);

#endif /* HUFFMAN_ALGORITHMS_UTIL_SLIDING_H */

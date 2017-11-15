/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_STANDARD_H
#define HUFFMAN_ALGORITHMS_UTIL_STANDARD_H

#include "../../datastructures/huffman_tree/huffman_tree.h"
#include "../../io/input/bit_input_stream.h"
#include "../../io/output/bit_output_stream.h"

/**
 * Traverses the tree in a DFS manner and assigns a character value to each
 * leaf.
 *
 * @param tree the Huffman tree
 * @param in the input stream
 */
void standard_assign_characters(huffman_tree *tree, bit_input_stream *in);

/**
 * Creates a Huffman tree from a binary input.
 *
 * @param root the root of the tree
 * @param input the input stream
 * @param assign_codes true to assign a code to every node
 */
void standard_build_tree_from_bits(huffman_node *root, bit_input_stream *input, bool assign_codes);

/**
 * Creates a Huffman tree from a frequency table.
 *
 * @param frequencies the frequency table
 */
huffman_tree *standard_build_tree_from_frequencies(uint_least32_t frequencies[]);

/**
 * Decodes the next character in the input stream.
 *
 * @param tree the Huffman tree to use
 * @param in the input stream
 * @return the decoded character
 */
byte standard_decode_character(huffman_node *tree, bit_input_stream *in);

/**
 * Traverses the tree in a DFS manner and prints all characters.
 *
 * @param root the root of the tree
 * @param out the output stream
 */
void standard_print_characters(huffman_node *root, bit_output_stream *out);

/**
 * Prints a Huffman tree to the supplied output stream.
 *
 * @param root the root of the tree to print
 * @param out the output stream to write to
 */
void standard_print_tree(huffman_node *root, bit_output_stream *out);

#endif /* HUFFMAN_ALGORITHMS_UTIL_STANDARD_H */
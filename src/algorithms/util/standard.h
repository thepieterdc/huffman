/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_STANDARD_H
#define HUFFMAN_ALGORITHMS_UTIL_STANDARD_H

#include "../../datastructures/huffman_tree/huffman_node.h"
#include "../../io/input/bit_input_stream.h"
#include "../../io/output/bit_output_stream.h"
#include "../../io/output/byte_output_stream.h"

/**
 * Traverses the tree in a DFS manner and assigns a character value to each
 * leaf.
 *
 * @param root the root of the tree
 * @param in the input stream
 */
void assign_characters(huffman_node *root, bit_input_stream *in);

/**
 * Creates a Huffman tree from a binary representation.
 *
 * @param root the root of the tree
 * @param input the input stream
 */
void build_tree(huffman_node *root, bit_input_stream *input);

/**
 * Decodes the next character in the input stream.
 *
 * @param tree the Huffman tree to use
 * @param in the input stream
 * @return the decoded character
 */
byte decode_character(huffman_node *tree, bit_input_stream *in);

/**
 * Decodes the final byte.
 *
 * @param tree the Huffman tree
 * @param byte the byte to decode
 * @param out the output stream to write to
 * @param amount the amount of bits to decode
 */
void decode_final_byte(huffman_node *tree, byte_output_stream *out, byte byte, size_t amount);

/**
 * Traverses the tree in a DFS manner and prints all characters.
 *
 * @param root the root of the tree
 * @param out the output stream
 */
void print_characters(huffman_node *root, bit_output_stream *out);

/**
 * Prints a Huffman tree to the supplied output stream.
 *
 * @param root the root of the tree to print
 * @param out the output stream to write to
 */
void print_tree(huffman_node *root, bit_output_stream *out);

#endif /* HUFFMAN_ALGORITHMS_UTIL_STANDARD_H */
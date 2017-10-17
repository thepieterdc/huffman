/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTILS_STANDARD_H
#define HUFFMAN_ALGORITHMS_UTILS_STANDARD_H

#include "../../datastructures/huffman_tree.h"

/**
 * Traverses the tree in a DFS manner and assigns a character value to each
 * leaf.
 *
 * @param root the root of the tree
 * @param in the input stream
 */
void assign_characters(huffman_node *root, bit_input_stream *in);

/**
 * Traverses the tree in a DFS manner and prints all bytes while filling the
 * code dictionary.
 *
 * @param root the root of the tree
 * @param code the code up to root
 * @param dictionary the dictionary to fill
 * @param out the output stream
 */
void build_dictionary(huffman_node *root, huffman_code *code, huffman_code **dictionary, bit_output_stream *out);

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

#endif /* HUFFMAN_ALGORITHMS_UTILS_STANDARD */

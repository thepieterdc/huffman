/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_STANDARD_H
#define HUFFMAN_ALGORITHMS_UTIL_STANDARD_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

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
 * @return the maximum tree depth (includes root)
 */
uint_fast8_t standard_build_tree_from_bits(huffman_node *root, bit_input_stream *input, bool assign_codes);

/**
 * Creates a Huffman tree from a frequency table.
 *
 * @param frequencies the frequency table
 * @return the created Huffman tree
 */
huffman_tree *standard_build_tree_from_frequencies(const uint_least64_t frequencies[]);

/**
 * Checks whether or not the tree contains random data. A tree contains random
 * data if, and only if, every code is 8 bits long (and therefore each
 * byte value exists in the tree).
 *
 * @param tree the Huffman tree
 * @return true if the tree contains random data
 */
bool standard_data_is_random(huffman_tree *tree);

/**
 * Decodes all characters in the input stream, assuming the data is random.
 *
 * @param in the input stream
 * @param out the output channel
 * @param tree the Huffman tree
 */
void standard_decode_random(byte_input_stream *in, FILE *out, huffman_tree *tree);

/**
 * Decodes all characters in the input stream.
 *
 * @param in the input stream
 * @param out the output channel
 * @param tree the Huffman tree
 * @param maxpath the maximum path length
 */
void standard_decode_regular(bit_input_stream *in, FILE *out, huffman_tree *tree, uint_fast8_t maxpath);

/**
 * Encodes all characters in the input stream, assuming the data is random.
 *
 * @param in the input stream
 * @param out the output channel
 * @param codes the codes for every character
 */
void standard_encode_random(byte_input_stream *in, FILE *out, uint_fast64_t codes[]);

/**
 * Encodes all characters in the input stream.
 *
 * @param in the input stream
 * @param out the output stream
 * @param codes the codes for every character
 * @param code_lengths the code lengths for every character
 */
void standard_encode_regular(byte_input_stream *in, bit_output_stream *out, uint_fast64_t codes[], const uint_fast8_t code_lengths[]);

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
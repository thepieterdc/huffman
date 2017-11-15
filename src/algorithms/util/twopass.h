/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_TWOPASS_H
#define HUFFMAN_ALGORITHMS_UTIL_TWOPASS_H

#include "../../datastructures/huffman_tree/adaptive_huffman_tree.h"
#include "../../io/input/bit_input_stream.h"
#include "../../io/output/bit_output_stream.h"

/**
 * Decodes a character and appends this to the output stream.
 *
 * @param tree the Huffman tree
 * @param in the input stream
 * @param out the output stream
 * @return the character
 */
byte twopass_decode_character(huffman_tree *tree, bit_input_stream *in, FILE *out);

/**
 * Parses a Huffman tree into an Adaptive Huffman tree; including setting the
 * order numbers and creating a NYT node.
 *
 * @param aht pointer to store the Adaptive Huffman tree
 * @param tree the original Huffman tree
 */
void twopass_parse_tree(adaptive_huffman_tree *aht, huffman_tree *tree);

#endif /* HUFFMAN_ALGORITHMS_UTIL_TWOPASS_H */
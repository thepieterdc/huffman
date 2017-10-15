/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATATYPES_HUFFMAN_CODE_H
#define HUFFMAN_DATATYPES_HUFFMAN_CODE_H

#include "bit.h"

/**
 * A code in a Huffman tree
 */
typedef struct huffman_code {
	uint64_t upper;
	uint_fast8_t upper_padding;
	uint64_t middle_upper;
	uint_fast8_t middle_upper_padding;
	uint64_t middle_lower;
	uint_fast8_t middle_lower_padding;
	uint64_t lower;
	uint_fast8_t lower_padding;
} huffman_code;

/**
 * Creates a new empty Huffman code.
 *
 * @return the created Huffman code.
 */
huffman_code *huffmancode_create();

/**
 * Creates a new Huffman code, left of its parent.
 *
 * @param parent the parent node
 * @return the created Huffman code
 */
huffman_code *huffmancode_create_left(huffman_code *parent);

/**
 * Creates a new Huffman code, right of its parent.
 *
 * @param parent the parent node
 * @return the created Huffman code
 */
huffman_code *huffmancode_create_right(huffman_code *parent);

/**
 * Frees the code allocated by a Huffman code.
 *
 * @param code the Huffman code
 */
void *huffmancode_free(huffman_code *code);

#endif /* HUFFMAN_DATATYPES_HUFFMAN_CODE_H */

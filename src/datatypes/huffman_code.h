/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATATYPES_HUFFMAN_CODE_H
#define HUFFMAN_DATATYPES_HUFFMAN_CODE_H

#include <unistd.h>
#include "bit.h"
#include "uint256_t.h"

/**
 * A code in a Huffman tree
 */
typedef struct huffman_code {
	uint256_t *code;
	size_t padding;
} huffman_code;

_int128_t test;

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
void huffmancode_free(huffman_code *code);

#endif /* HUFFMAN_DATATYPES_HUFFMAN_CODE_H */

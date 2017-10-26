/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATATYPES_HUFFMAN_CODE_H
#define HUFFMAN_DATATYPES_HUFFMAN_CODE_H

#include <unistd.h>
#include "bit.h"

/**
 * A code in a Huffman tree
 */
typedef struct huffman_code {
	uint_least64_t code;
	uint_least8_t padding;
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

#endif /* HUFFMAN_DATATYPES_HUFFMAN_CODE_H */

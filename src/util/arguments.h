/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_ARGUMENTS_H
#define HUFFMAN_UTIL_ARGUMENTS_H

/**
 * A compression function.
 */
typedef void (*_compressionfunction)();

/**
 * A decompression function.
 */
typedef void (*_decompressionfunction)();

/**
 * Algorithms.
 */
enum algorithm {
	STANDARD, ADAPTIVE, ADAPTIVE_SLIDING, TWO_PASS, BLOCKWISE
};

/**
 * Operation modes.
 */
enum mode {
	COMPRESS, DECOMPRESS
};

/**
 * Compression functions.
 */
extern _compressionfunction compressionfunctions[1];

/**
 * Decompression functions.
 */
extern _decompressionfunction decompressionfunctions[1];

#endif /* HUFFMAN_UTIL_ARGUMENTS_H */
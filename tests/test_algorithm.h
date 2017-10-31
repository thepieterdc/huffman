/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_ALGORITHM_H
#define HUFFMAN_TEST_ALGORITHM_H

#include "../src/util/arguments.h"

/** Tests: huffman_standard_compress(), huffman_standard_decompress(). */
char *test_algorithm_adaptive();

/** Tests: huffman_standard_compress(), huffman_standard_decompress(). */
char *test_algorithm_standard();

/**
 * Tests a Huffman algorithm.
 *
 * @param encoder the encoding function
 * @param decoder the decoding function
 * @return null if test was succesful
 */
char *test_huffman_algorithm(_huffmanfunction encoder, _huffmanfunction decoder);

#endif /* HUFFMAN_TEST_ALGORITHM_H */

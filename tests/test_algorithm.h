/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_ALGORITHM_H
#define HUFFMAN_TEST_ALGORITHM_H

#include "../src/util/arguments.h"

/**
 * Tests a Huffman algorithm.
 *
 * @param encoder the encoding function
 * @param decoder the decoding function
 * @return null if test was succesful
 */
char *test_huffman_algorithm(_huffmanfunction encoder, _huffmanfunction decoder);

#endif /* HUFFMAN_TEST_ALGORITHM_H */

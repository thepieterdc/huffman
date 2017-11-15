/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_ALGORITHM_H
#define HUFFMAN_TEST_ALGORITHM_H

#include "../src/util/arguments.h"

/** Tests: huffman_adaptive_compress(), huffman_adaptive_decompress(). */
const char *test_algorithm_adaptive();

/** Tests: huffman_blockwise_compress(), huffman_blockwise_decompress(). */
const char *test_algorithm_blockwise();

/** Tests: huffman_sliding_compress(), huffman_sliding_decompress(). */
const char *test_algorithm_sliding();

/** Tests: huffman_standard_compress(), huffman_standard_decompress(). */
const char *test_algorithm_standard();

/** Tests: huffman_twopass_compress(), huffman_twopass_decompress(). */
const char *test_algorithm_twopass();

#endif /* HUFFMAN_TEST_ALGORITHM_H */

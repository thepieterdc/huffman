/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_ALGORITHMS_UTIL_COMMON_H
#define HUFFMAN_ALGORITHMS_UTIL_COMMON_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include "../../io/input/bit_input_stream.h"

/**
 * Finalizes the inputstream for decoding.
 *
 * @param in the inputstream
 * @return the amount of bits left to decode
 */
size_t huffman_finalize_input(bit_input_stream *in);

/**
 * Prepares the outputstream for decoding.
 *
 * @param out the outputstream
 */
void huffman_prepare_output(FILE *out);

#endif /* HUFFMAN_ALGORITHMS_UTIL_COMMON_H */
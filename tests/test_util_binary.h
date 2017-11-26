/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_UTIL_BINARY_H
#define HUFFMAN_TEST_UTIL_BINARY_H

/** Tests: bit_to_bitchar(). */
const char *test_bit_to_bitchar();

/** Tests: bitchar_to_bit(). */
const char *test_bitchar_to_bit();

/** Tests: bitmask_n(). */
const char *test_bitmask_n();

/** Tests: bitmask_n_offset(). */
const char *test_bitmask_n_offset();

/** Tests: bitstring_to_byte(). */
const char *test_bitstring_to_byte();

/** Tests: byte_to_bitstring(). */
const char *test_byte_to_bitstring();

/** Tests: nth_bit_in_byte_lsb(). */
const char *test_nth_bit_in_byte_lsb();

/** Tests: nth_bit_in_byte_msb(). */
const char *test_nth_bit_in_byte_msb();

#endif /* HUFFMAN_TEST_UTIL_BINARY_H */
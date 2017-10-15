/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_DATATYPE_UINT256T_H
#define HUFFMAN_TEST_DATATYPE_UINT256T_H

/** Tests: uint256_copy(). */
char *test_uint256t_copy();

/** Tests: uint256_create(). */
char *test_uint256t_create();

/** Tests: uint256_copy(). */
char *test_uint256t_equals();

/** Tests: uint256_set_lsb(), uint256_set_msb(). */
char *test_uint256t_set_lsb_msb();

/** Tests: uint256_shift_left(), uint256_shift_right(), uint256_shift_left_assign(), uint256_shift_right_assign(). */
char *test_uint256t_shift();

/** Tests: uint256_to_bitstring(). */
char *test_uint256t_to_bitstring();

#endif /* HUFFMAN_TEST_DATATYPE_UINT256T_H */
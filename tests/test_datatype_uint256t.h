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

/** Tests: uint256_equals(), uint256_is_zero(). */
char *test_uint256t_equals_is_zero();

/** Tests: uint256_nth_bit(). */
char *test_uint256t_nth_bit();

/** Tests: uint256_set_lsb(), uint256_set_msb(). */
char *test_uint256t_set_lsb_msb();

/** Tests: uint256_shift_left(), uint256_shift_right(), uint256_shift_left_assign(), uint256_shift_right_assign(). */
char *test_uint256t_shift();

#endif /* HUFFMAN_TEST_DATATYPE_UINT256T_H */
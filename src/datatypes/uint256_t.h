/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATATYPES_UINT256_T_H
#define HUFFMAN_DATATYPES_UINT256_T_H

#include <unistd.h>
#include "bit.h"

/**
 * A 256-bit integer.
 *
 * value: [upper, middle-upper, middle-lower, lower]
 */
typedef struct uint256_t {
	uint64_t value[4];
} uint256_t;

/**
 * Creates a new uint256 from a given value.
 *
 * @param value the value to assign
 * @return the created uint256
 */
uint256_t *uint256(uint64_t value);

/**
 * Creates a new uint256 from an existing uint256.
 *
 * @param old the old uint256 to copy
 * @return the copied uint256
 */
uint256_t *uint256_copy(const uint256_t *old);

/**
 * Compares two uint256's for equality.
 *
 * @param first first value
 * @param second second value
 * @return true if both are equal
 */
bool uint256_equals(uint256_t *first, uint256_t *second);

/**
 * Returns whether an uint256 equals to zero.
 *
 * @param value the value to check
 * @return true if zero, false otherwise
 */
bool uint256_is_zero(uint256_t *value);

/**
 * Gets the value of the n-th bit (starting from LSB).
 *
 * @param value the uint256
 * @param n the n-th bit will be returned
 * @return the n-th bit of the value
 */
bit uint256_nth_bit(uint256_t *value, uint8_t n);

/**
 * Sets the least significant bit.
 *
 * @param value the uint256 to modify
 * @param lsb the value (0 or 1) to set the lsb to
 */
void uint256_set_lsb(uint256_t *value, bit lsb);

/**
 * Sets the most significant bit.
 *
 * @param value the uint256 to modify
 * @param msb the value (0 or 1) to set the MSB to
 * @return a new uint256 with the modified MSB
 */
void uint256_set_msb(uint256_t *value, bit msb);

/**
 * Shifts the supplied uint256 to the left over 1 bit (<<).
 *
 * @param value the uint256 to shift
 * @return the shifted value
 */
uint256_t *uint256_shift_left(uint256_t *value);

/**
 * Shifts the given uint256 to the left over 1 bit (<<=).
 *
 * @param value the uint256 to shift
 * @return the modified uint256 (fluent)
 */
uint256_t *uint256_shift_left_assign(uint256_t *value);

/**
 * Shifts the supplied uint256 to the right over 1 bit (logical >>).
 *
 * @param value the uint256 to shift
 * @return the shifted value
 */
uint256_t *uint256_shift_right(const uint256_t *value);

/**
 * Shifts the given uint256 to the right over 1 bit (logical >>=).
 *
 * @param value the uint256 to shift
 * @return the modified uint256 (fluent)
 */
uint256_t *uint256_shift_right_assign(uint256_t *value);

#endif /* HUFFMAN_DATATYPES_UINT256_T_H */

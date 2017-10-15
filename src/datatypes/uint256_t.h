/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATATYPES_UINT256_T_H
#define HUFFMAN_DATATYPES_UINT256_T_H

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "bit.h"
#include "../util/errors.h"
#include "../util/logging.h"
#include "../util/binary.h"

static uint_least64_t MSB = 1 << 63;

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
uint256_t *uint256(uint64_t value) {
	uint256_t *ret = (uint256_t *) malloc(sizeof(uint256_t));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->value[3] = value;
	}
	return ret;
}

/**
 * Creates a new uint256 from an existing uint256.
 *
 * @param old the old uint256 to copy
 * @return the copied uint256
 */
uint256_t *uint256_copy(uint256_t *old) {
	uint256_t *ret = (uint256_t *) malloc(sizeof(uint256_t));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		memcpy(&ret->value, &old->value, 4 * sizeof(uint64_t));
	}
	return ret;
}

/**
 * Shifts the supplied uint256 to the left over 1 bit (<<).
 *
 * @param value the uint256 to shift
 * @return the shifted value
 */
uint256_t *uint256_shift_left(uint256_t *value) {
	uint256_t *ret = uint256_copy(value);
	ret->value[0] = value->value[0] << 1;
	bit carry = 0;
	for (size_t p = 2; p >= 0; --p) {
		carry = (bit) (value->value[p] & MSB);
		ret->value[p] = value->value[p] << 1;
		ret->value[p + 1] |= carry;
	}
	return ret;
}

/**
 * Shifts the supplied uint256 to the right over 1 bit (logical >>).
 *
 * @param value the uint256 to shift
 * @return the shifted value
 */
uint256_t *uint256_shift_right(uint256_t *value) {
	uint256_t *ret = uint256_copy(value);
	ret->value[3] = value->value[3] >> 1;
	bit carry = 0;
	for (size_t p = 1; p < 3; ++p) {
		carry = (bit) (value->value[p] & 1);
		ret->value[p] = value->value[p] >> 1;
		ret->value[p - 1] |= (carry << MSB);
	}
	return ret;
}

/**
 * Converts a uint256 to a string of bits, for printing. Padding in the front
 * is not applied.
 *
 * @param value the uint256
 * @param dest the location to store the string of bits
 */
void uint256_to_bitstring(uint256_t *value, char *dest) {
	size_t counter = 255;
	for (size_t p = 0; p < 4; ++p) {
		if (value->value[p] != 0) {
			uint64_t leftover = value->value[p];
			for (size_t b = 0; b < 64 && leftover != 0; ++b) {
				dest[counter--] = bit_to_bitchar((bit) (leftover & 1));
				leftover >>= 1;
			}
		}
	}
}

#endif /* HUFFMAN_DATATYPES_UINT256_T_H */

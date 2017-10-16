/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <memory.h>
#include "uint256_t.h"
#include "bit.h"
#include "../util/logging.h"
#include "../util/errors.h"

/**
 * Most significant bit.
 */
static uint_least64_t uint64_msb = ((uint_least64_t) 1) << 63;

uint256_t *uint256(uint64_t value) {
	uint256_t *ret = (uint256_t *) malloc(sizeof(uint256_t));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->value[0] = ret->value[1] = ret->value[2] = 0;
		ret->value[3] = value;
	}
	return ret;
}

uint256_t *uint256_copy(const uint256_t *old) {
	uint256_t *ret = (uint256_t *) malloc(sizeof(uint256_t));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		memcpy(&ret->value, &old->value, 4 * sizeof(uint64_t));
	}
	return ret;
}

bool uint256_equals(uint256_t *first, uint256_t *second) {
	bool equal = true;
	for (size_t p = 0; p < 4; ++p) {
		if (first->value[p] != second->value[p]) {
			return false;
		}
	}
	return equal;
}

bool uint256_is_zero(uint256_t *value) {
	for (size_t p = 0; p < 4; ++p) {
		if (value->value[p] != 0) return false;
	}
	return true;
}

void uint256_set_lsb(uint256_t *value, bit lsb) {
	if (lsb) {
		value->value[3] |= 1;
	} else {
		value->value[3] &= 0;
	}
}

void uint256_set_msb(uint256_t *value, bit msb) {
	if (msb) {
		value->value[0] |= uint64_msb;
	} else {
		value->value[0] &= ~(uint64_msb);
	}
}

uint256_t *uint256_shift_left(uint256_t *value) {
	uint256_t *ret = uint256_copy(value);
	ret->value[0] = value->value[0] << 1;
	bit carry = 0;
	for (size_t p = 1; p < 4; ++p) {
		carry = (bit) (value->value[p] & uint64_msb);
		ret->value[p] = value->value[p] << 1;
		ret->value[p - 1] |= carry;
	}
	return ret;
}

uint256_t *uint256_shift_left_assign(uint256_t *value) {
	value->value[0] = value->value[0] << 1;
	bit carry = 0;
	for (size_t p = 1; p < 4; ++p) {
		carry = (bit) (value->value[p] & uint64_msb);
		value->value[p] = value->value[p] << 1;
		value->value[p - 1] |= carry;
	}
	return value;
}

uint256_t *uint256_shift_right(const uint256_t *value) {
	uint256_t *ret = uint256_copy(value);
	ret->value[3] = value->value[3] >> 1;
	bit carry = 0;
	for (size_t p = 3; p > 0; --p) {
		carry = (bit) (value->value[p - 1] & 1);
		ret->value[p - 1] = value->value[p - 1] >> 1;
		if (carry == 1) {
			ret->value[p] |= uint64_msb;
		}
	}
	return ret;
}

uint256_t *uint256_shift_right_assign(uint256_t *value) {
	value->value[3] = value->value[3] >> 1;
	bit carry = 0;
	for (size_t p = 3; p > 0; --p) {
		carry = (bit) (value->value[p - 1] & 1);
		value->value[p - 1] = value->value[p - 1] >> 1;
		if (carry == 1) {
			value->value[p] |= uint64_msb;
		}
	}
	return value;
}
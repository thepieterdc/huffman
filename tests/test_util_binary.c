/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <stdio.h>
#include "test_unit.h"
#include "test_util_binary.h"
#include "../src/util/binary.h"
#include "../src/util/string.h"

const char *test_bit_to_bitchar() {
	assertEquals(bit_to_bitchar(1), '1');
	assertEquals(bit_to_bitchar(0), '0');
	return 0;
}

const char *test_bitchar_to_bit() {
	assertEquals(bitchar_to_bit('1'), 1);
	assertEquals(bitchar_to_bit('0'), 0);
	return 0;
}

const char *test_bitmask_n() {
	assertEquals(bitmask_n(0), 0x0);
	assertEquals(bitmask_n(1), 0x1);
	assertEquals(bitmask_n(2), 0x3);
	assertEquals(bitmask_n(3), 0x7);
	assertEquals(bitmask_n(4), 0xF);
	assertEquals(bitmask_n(5), 0x1F);
	assertEquals(bitmask_n(6), 0x3F);
	assertEquals(bitmask_n(7), 0x7F);
	assertEquals(bitmask_n(8), 0xFF);
	return 0;
}

const char *test_bitmask_n_offset() {
	for (size_t i = 0; i < BITS_IN_BYTE; ++i) {
		assertEquals(bitmask_n_offset(1, i), 0b1 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 1; ++i) {
		assertEquals(bitmask_n_offset(2, i), 0b11 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 2; ++i) {
		assertEquals(bitmask_n_offset(3, i), 0b111 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 3; ++i) {
		assertEquals(bitmask_n_offset(4, i), 0b1111 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 4; ++i) {
		assertEquals(bitmask_n_offset(5, i), 0b11111 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 5; ++i) {
		assertEquals(bitmask_n_offset(6, i), 0b111111 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 6; ++i) {
		assertEquals(bitmask_n_offset(7, i), 0b1111111 << i);
	}
	for (size_t i = 0; i < BITS_IN_BYTE - 7; ++i) {
		assertEquals(bitmask_n_offset(8, i), 0b11111111 << i);
	}
	return 0;
}

const char *test_bitstring_to_byte() {
	assertEquals(bitstring_to_byte("10001"), 0b10001);
	assertEquals(bitstring_to_byte("0"), 0);
	return 0;
}

const char *test_byte_to_bitstring() {
	string bitstring1 = byte_to_bitstring(0b01100);
	assertTrue(str_equals(bitstring1, "00001100"));
	string bitstring2 = byte_to_bitstring(0b10001);
	assertTrue(str_equals(bitstring2, "00010001"));
	
	free(bitstring1);
	free(bitstring2);
	return 0;
}

const char *test_nth_bit_in_byte_lsb() {
	for (size_t i = 0; i < BITS_IN_BYTE; ++i) {
		byte b = (byte) (1 << i);
		for (size_t j = 0; j < BITS_IN_BYTE; ++j) {
			assertEquals(nth_bit_in_byte_lsb(b, j), i == j);
		}
	}
	return 0;
}

const char *test_nth_bit_in_byte_msb() {
	for (size_t i = 0; i < BITS_IN_BYTE; ++i) {
		byte b = (byte) (1 << i);
		for (size_t j = BITS_IN_BYTE; j > 0; --j) {
			assertEquals(nth_bit_in_byte_msb(b, j - 1), BITS_IN_BYTE - i == j);
		}
	}
	return 0;
}
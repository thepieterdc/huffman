/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
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

const char *test_bitmask_n_bits() {
	assertEquals(bitmask_n_bits(0), 0x0);
	assertEquals(bitmask_n_bits(1), 0x1);
	assertEquals(bitmask_n_bits(2), 0x3);
	assertEquals(bitmask_n_bits(3), 0x7);
	assertEquals(bitmask_n_bits(4), 0xF);
	assertEquals(bitmask_n_bits(5), 0x1F);
	assertEquals(bitmask_n_bits(6), 0x3F);
	assertEquals(bitmask_n_bits(7), 0x7F);
	assertEquals(bitmask_n_bits(8), 0xFF);
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
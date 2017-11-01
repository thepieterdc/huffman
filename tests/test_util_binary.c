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
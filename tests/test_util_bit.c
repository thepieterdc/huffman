/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_unit.h"
#include "test_util_bit.h"
#include "../src/util/bit.h"

char *test_bitchar_to_bit() {
	assertThat(bitchar_to_bit('1') == 1);
	assertThat(bitchar_to_bit('0') == 0);
	return 0;
}

char *test_bitstring_to_byte() {
	assertThat(bitstring_to_byte("10001") == 0b10001);
	assertThat(bitstring_to_byte("0") == 0);
	return 0;
}
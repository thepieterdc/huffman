/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <string.h>
#include "binary.h"
#include "memory.h"

inline char bit_to_bitchar(const bit b) {
	return (char) (b ? 49 : 48);
}

inline bit bitchar_to_bit(const char c) {
	return c == 49;
}

byte bitstring_to_byte(string s) {
	byte ret = 0;
	for (size_t c = 0; c < strlen(s); ++c) {
		ret <<= 1;
		ret |= bitchar_to_bit(s[c]);
	}
	return ret;
}

string byte_to_bitstring(byte b) {
	string ret = (string) mallocate((8 + 1) * sizeof(char));
	ret[8] = '\0';
	
	for (size_t i = 0; i < 8; ++i) {
		ret[7 - i] = bit_to_bitchar((bit) (b & 1));
		b >>= 1;
	}
	return ret;
}
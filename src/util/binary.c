/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <string.h>
#include <unistd.h>
#include "binary.h"

bit bitchar_to_bit(char c) {
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
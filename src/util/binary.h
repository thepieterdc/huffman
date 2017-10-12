/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_BINARY_H
#define HUFFMAN_UTIL_BINARY_H

#include <stdint.h>
#include "../datatypes/bit.h"
#include "../datatypes/string.h"

/**
 * Converts a bit to a character representation.
 *
 * @param b the bit to convert
 * @return the character representation
 */
char bit_to_bitchar(bit b);

/**
 * Converts a character to a bit.
 *
 * @param c character 1 or 0
 * @return bit 1 or 0
 */
bit bitchar_to_bit(char c);

/**
 * Converts a string of bits to a byte.
 *
 * @param s the string to convert
 * @return the byte
 */
byte bitstring_to_byte(string s);

/**
 * Converts a byte to a string representation.
 *
 * @param b the byte to convert
 * @return the bitstring
 */
string byte_to_bitstring(byte b);

#endif /* HUFFMAN_UTIL_BINARY_H */

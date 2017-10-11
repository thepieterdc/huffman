/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_BINARY_H
#define HUFFMAN_UTIL_BINARY_H

#include <stdint.h>
#include "string.h"

typedef bool bit;
typedef uint8_t byte;

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

#endif /* HUFFMAN_UTIL_BINARY_H */

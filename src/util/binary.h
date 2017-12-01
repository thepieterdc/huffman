/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_BINARY_H
#define HUFFMAN_UTIL_BINARY_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdint.h>
#include "../datatypes/bit.h"
#include "../datatypes/string.h"

/**
 * A mask that covers all bits in a byte.
 */
#define BYTE_MASK 0xFF

/**
 * Converts a bit to a character representation.
 *
 * @param b the bit to convert
 * @return the character representation
 */
#define bit_to_bitchar(b) (char) ((b) ? 49 : 48)

/**
 * Converts a character to a bit.
 *
 * @param c character 1 or 0
 * @return bit 1 or 0
 */
#define bitchar_to_bit(c) ((c) == '1')

/**
 * A bitmask to get n bits from a byte.
 *
 * @param n the amount of bits to fetch
 * @return the mask to use
 */
#define bitmask_n(n) ((1 << (n))-1)

/**
 * A bitmask to get n bits from a byte given an offset (LSB based).
 *
 * @param n the amount of bits to fetch
 * @param o the offset (LSB based)
 * @return the mask to use
 */
#define bitmask_n_offset(n, o) ((bitmask_n(n) << (o)))

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

/**
 * Gets the {n}-th bit in a byte (LSB-based). Zero based.
 *
 * @param b the byte
 * @param n the LSB-based position of the bit to retrieve
 * @return the value of the bit at position n, starting from the right
 */
#define nth_bit_in_byte_lsb(b, n) (bit) ((b) & (1 << (n)))

/**
 * Gets the {n}-th bit in a byte (MSB-based). Zero based.
 *
 * @param b the byte
 * @param n the MSB-based position of the bit to retrieve
 * @return the value of the bit at position n, starting from the left
 */
#define nth_bit_in_byte_msb(b, n) (bit) ((b) & (0x80 >> (n)))

/**
 * Converts a uint64 to a string representation.
 *
 * @param b the uint64 to convert
 * @return the bitstring
 */
string uint64_to_bitstring(uint64_t b);

#define GIBIBYTE(x)   ((size_t) (x) << 30)
#define KIBIBYTE(x)   ((size_t) (x) << 10)
#define MEBIBYTE(x)   ((size_t) (x) << 20)

#endif /* HUFFMAN_UTIL_BINARY_H */

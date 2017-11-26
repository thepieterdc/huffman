/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATATYPES_BIT_H
#define HUFFMAN_DATATYPES_BIT_H

#include <stdbool.h>
#include <stdint.h>

/**
 * The amount of bits in one byte.
 */
#define BITS_IN_BYTE 8

/**
 * A single bit.
 */
typedef bool bit;

/**
 * A byte, 8 bits.
 */
typedef uint_fast8_t byte;

#endif /* HUFFMAN_DATATYPES_BIT_H */

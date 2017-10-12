/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_STRING_H
#define HUFFMAN_UTIL_STRING_H

#include <stdbool.h>
#include "../datatypes/string.h"

/**
 * Converts a character digit to it's corresponding integer.
 *
 * @param c the character
 * @return the corresponding integer
 */
int char_to_int(char c);

/**
 * Concatenates 2 strings into one.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return the concatenated string
 */
string str_concat(string s1, string s2);

/**
 * Returns whether 2 strings are equal.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return true if both strings are equal
 */
bool str_equals(string s1, string s2);

#endif /* HUFFMAN_UTIL_STRING_H */
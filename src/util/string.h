/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_STRING_H
#define HUFFMAN_UTIL_STRING_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdbool.h>
#include <string.h>
#include "../datatypes/string.h"

/**
 * Converts a character digit to it's corresponding integer.
 *
 * @param c the character
 * @return the corresponding integer
 */
#define char_to_int(c) ((c) - '0')

/**
 * Concatenates 2 strings into one.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return the concatenated string
 */
string str_concat(string s1, string s2);

/**
 * Returns whether {haystack} contains {needle}.
 *
 * @param haystack the string to search in
 * @param needle the string to find in haystack
 * @return true if haystack contains needle
 */
#define str_contains(haystack, needle) (bool) (strstr((haystack), (needle)) != NULL)

/**
 * Returns whether 2 strings are equal.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return true if both strings are equal
 */
#define str_equals(s1, s2) (bool) (strcmp((s1), (s2)) == 0)

#endif /* HUFFMAN_UTIL_STRING_H */
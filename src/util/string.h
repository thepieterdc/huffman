/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_STRING_H
#define HUFFMAN_UTIL_STRING_H

typedef char* string;

/**
 * Concatenates 2 strings into one.
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return the concatenated string
 */
string concat(string s1, string s2);

#endif /* HUFFMAN_UTIL_STRING_H */
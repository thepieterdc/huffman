/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <string.h>
#include "memory.h"
#include "string.h"

string str_concat(string s1, string s2) {
	string result = (string) mallocate((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

inline bool str_contains(string haystack, string needle) {
	return strstr(haystack, needle) != NULL;
}

inline bool str_equals(string s1, string s2) {
	return strcmp(s1, s2) == 0;
}
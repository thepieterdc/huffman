/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <string.h>
#include "string.h"

int char_to_int(size_t c) {
	return c - '0';
}

string str_concat(string s1, string s2) {
	string result = (string) malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

bool str_equals(string s1, string s2) {
	return strcmp(s1, s2) == 0;
}
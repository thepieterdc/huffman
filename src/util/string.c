/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "memory.h"
#include "string.h"

string str_concat(string s1, string s2) {
	string result = (string) mallocate((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}
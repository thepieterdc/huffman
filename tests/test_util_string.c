/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"
#include "test_util_string.h"
#include "../src/util/string.h"

const char *test_char_to_int() {
	for (size_t i = 0; i < 9; ++i) {
		assertEquals(char_to_int((char) (48 + i)), i);
	}
	return 0;
}

const char *test_string_concat() {
	char s1[] = "first";
	char s2[] = "last";
	char s3[] = "everything";
	
	string s1s2 = str_concat(s1, s2);
	assertTrue(str_equals(s1s2, "firstlast"));
	
	string s1s2s3 = str_concat(s1s2, s3);
	assertTrue(str_equals(s1s2s3, "firstlasteverything"));
	
	free(s1s2);
	free(s1s2s3);
	return 0;
}

const char *test_string_equals() {
	char s1[] = "equals";
	char s2[] = "notequals";
	char s3[] = "equals";
	
	assertFalse(str_equals(s1, s2));
	assertTrue(str_equals(s1, s3));
	assertFalse(str_equals(s2, s1));
	assertFalse(str_equals(s2, s3));
	assertTrue(str_equals(s3, s1));
	assertFalse(str_equals(s3, s2));
	
	return 0;
}
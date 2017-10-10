/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"
#include "test_util_string.h"
#include "../src/util/string.h"

char *test_string_concat() {
	char s1[] = "first";
	char s2[] = "last";
	char s3[] = "everything";
	
	string s1s2 = str_concat(s1, s2);
	assertThat(str_equals(s1s2, "firstlast"));
	
	string s1s2s3 = str_concat(s1s2, s3);
	assertThat(str_equals(s1s2s3, "firstlasteverything"));
	
	free(s1s2);
	free(s1s2s3);
	return 0;
}

char *test_string_equals() {
	char s1[] = "equals";
	char s2[] = "notequals";
	char s3[] = "equals";
	
	assertThat(!str_equals(s1, s2));
	assertThat(str_equals(s1, s3));
	assertThat(!str_equals(s2, s1));
	assertThat(!str_equals(s2, s3));
	assertThat(str_equals(s3, s1));
	assertThat(!str_equals(s3, s2));
	
	return 0;
}
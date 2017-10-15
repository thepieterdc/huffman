/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <assert.h>
#include "test_unit.h"

int testunit_tests_ok = 0;
int testunit_tests_total = 0;

static char message_string[255 + 1];

char *_testunit_assert_failed(const char *func, int line, const char *code) {
	snprintf(message_string, 255, "%s (assertion: %s @ line: %d)", func, code, line);
	
	message_string[255] = '\0';
	
	return message_string;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <assert.h>
#include "test_unit.h"

int testunit_assertions = 0;
int testunit_tests_ok = 0;
int testunit_tests_total = 0;

static char message_string[255 + 1];

static char *_testunit_assert_failed(const char *func, const int line, const char *msg) {
	snprintf(message_string, 255, "%s (%s @ line: %d)", func, msg, line);
	
	message_string[255] = '\0';
	
	return message_string;
}

char *_testunit_assert_equals_failed(const char *fn, int line, const char *one, const char *two) {
	char assert[256] = {'\0'};
	snprintf(assert, 255, "%s should equal %s", one, two);
	return _testunit_assert_failed(fn, line, assert);
}

char *_testunit_assert_false_failed(const char *fn, const int line, const char *condition) {
	char assert[256] = {'\0'};
	snprintf(assert, 255, "%s must be false", condition);
	return _testunit_assert_failed(fn, line, assert);
}

char *_testunit_assert_notequals_failed(const char *fn, int line, const char *one, const char *two) {
	char assert[256] = {'\0'};
	snprintf(assert, 255, "%s may not be equal to %s", one, two);
	return _testunit_assert_failed(fn, line, assert);
}

char *_testunit_assert_notnull_failed(const char *fn, int line, const char *var) {
	char assert[256] = {'\0'};
	snprintf(assert, 255, "%s is NULL", var);
	return _testunit_assert_failed(fn, line, assert);
}

char *_testunit_assert_null_failed(const char *fn, int line, const char *var) {
	char assert[256] = {'\0'};
	snprintf(assert, 255, "%s must be NULL", var);
	return _testunit_assert_failed(fn, line, assert);
}

char *_testunit_assert_true_failed(const char *fn, const int line, const char *condition) {
	char assert[256] = {'\0'};
	snprintf(assert, 255, "%s must be true", condition);
	return _testunit_assert_failed(fn, line, assert);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"

#include "test_util_bitprinter.h"

/**
 * Runs all tests.
 *
 * @return N/A
 */
static char *all_tests() {
	/** Test: test_util_bitprinter. */
	test(test_bitprinter_create_free);
	test(test_bitprinter_add_bit);
	return 0;
}

int main(void) {
	info("Running tests...");
	
	all_tests();
	
	char msg[25];
	sprintf(msg, "%d/%d tests succeeded.", testunit_tests_ok, testunit_tests_total);
	if (testunit_tests_ok == testunit_tests_total) {
		success(msg);
	} else {
		warning(msg);
	}
	return 0;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"
#include "../src/util/logging.h"
#include "../src/util/string.h"

#include "test_util_linked_list.h"

/**
 * Runs all tests.
 *
 * @return N/A
 */
static string all_tests() {
	/** Test: linked_list. */
	test(test_ll_create_free);
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
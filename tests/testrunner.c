/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"

#include "test_util_bitstream.h"

#include "test_datastructure_queue.h"
#include "test_util_string.h"

/**
 * Runs all tests.
 *
 * @return N/A
 */
static char *all_tests() {
	/** Test: datastructures/queue. */
	test(test_queue_create_free);
	test(test_queue_push_peek_pop);
	
	/** Test: util/bitstream. */
	test(test_bs_add_bit);
	test(test_bs_add_byte);
	test(test_bs_create_free);
	
	/** Test: util/string. */
	test(test_string_concat);
	test(test_string_equals);
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
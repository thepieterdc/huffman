/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"

#include "test_datastructure_queue.h"
#include "test_util_binary.h"
#include "test_io_input_inputstream.h"
#include "test_util_string.h"
#include "test_io_input_intinputstream.h"

/**
 * Runs all tests.
 *
 * @return N/A
 */
static char *all_tests() {
	/** Test: datastructures/queue. */
	test(test_queue_create_free);
	test(test_queue_empty);
	test(test_queue_push_peek_pop);
	
	/** Test: io/input/inputstream. */
	test(test_io_is_create_free);
	test(test_io_is_feed_read_count);
	
	/** Test: io/input/intinputstream. */
	test(test_io_iis_create_free);
	test(test_io_iis_consume_read_count);
	test(test_io_iis_feed_read_count);
	
	/** Test: util/bit. */
	test(test_bitchar_to_bit);
	test(test_bitstring_to_byte);
	
	/** Test: util/string. */
	test(test_char_to_int);
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
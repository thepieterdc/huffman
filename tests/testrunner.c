/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"
#include "test_datastructure_queue.h"
#include "test_io_input_bitinputstream.h"
#include "test_io_input_byteinputstream.h"
#include "test_io_input_inputstream.h"
#include "test_io_input_intinputstream.h"
#include "test_io_output_byteoutputstream.h"
#include "test_io_output_intoutputstream.h"
#include "test_io_output_outputstream.h"
#include "test_util_binary.h"
#include "test_util_string.h"

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
	
	/** Test: io/input/bit_input_stream. */
	test(test_io_bis_create_free);
	test(test_io_bis_read_bit_count);
	test(test_io_bis_read_byte_count);
	
	/** Test: io/input/byte_input_stream. */
	test(test_io_byis_create_free);
	test(test_io_byis_consume_read_count);
	test(test_io_byis_feed_read_count);
	
	/** Test: io/input/input_stream. */
	test(test_io_is_create_free);
	test(test_io_is_feed_read_count);
	
	/** Test: io/input/int_input_stream. */
	test(test_io_iis_create_free);
	test(test_io_iis_consume_read_count);
	test(test_io_iis_feed_read_count);
	
	/** Test: io/output/byte_output_stream. */
	test(test_io_byos_create_free);
	test(test_io_byos_feed_flush_count);
	
	/** Test: io/output/int_output_stream. */
	test(test_io_ios_create_free);
	test(test_io_ios_feed_flush_count);
	
	/** Test: io/output/output_stream. */
	test(test_io_os_create_free);
	test(test_io_os_feed_read_count);
	
	/** Test: util/binary. */
	test(test_bit_to_bitchar);
	test(test_bitchar_to_bit);
	test(test_bitstring_to_byte);
	test(test_byte_to_bitstring);
	
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
	return testunit_tests_ok != testunit_tests_total;
}
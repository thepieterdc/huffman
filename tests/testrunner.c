/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"
#include "test_datastructure_huffmannode.h"
#include "test_datastructure_minheap.h"
#include "test_datastructure_bytequeue.h"
#include "test_io_input_bitinputstream.h"
#include "test_io_input_byteinputstream.h"
#include "test_io_output_bitoutputstream.h"
#include "test_util_arguments.h"
#include "test_util_binary.h"
#include "test_util_string.h"
#include "test_datatype_huffmancode.h"
#include "test_algorithm.h"

/**
 * Runs all tests.
 *
 * @return N/A
 */
static const char *all_tests() {
	/** Test: algorithms. */
	test(test_algorithm_adaptive);
	test(test_algorithm_blockwise);
	test(test_algorithm_sliding);
	test(test_algorithm_standard);
	test(test_algorithm_twopass);

	/** Test: datastructures/huffman_node. */
	test(test_huffmannode_create_free);

	/** Test: datastructures/min_heap. */
	test(test_minheap_create_free);
	test(test_minheap_insert_find_extract_min);

	/** Test: datastructures/byte_queue. */
	test(test_byte_queue_create_free);
	test(test_byte_queue_empty);
	test(test_byte_queue_push_peek_pop);

	/** Test: datatypes/huffman_code. */
	test(test_huffmancode_create_left_right);

	/** Test: io/input/bit_input_stream. */
	test(test_io_bis_create_free);
	test(test_io_bis_read_bit);
	test(test_io_bis_read_byte);

	/** Test: io/input/byte_input_stream. */
	test(test_io_byis_create_free);
	test(test_io_byis_read);

	/** Test: io/output/bit_output_stream. */
	test(test_io_bos_create_free);
	test(test_io_bos_feed_bit_flush);
	test(test_io_bos_feed_bit_pad_flush);
	test(test_io_bos_feed_byte_flush);

	/** Test: util/arguments. */
	test(test_arguments_algorithm);
	test(test_arguments_mode);
	test(test_arguments_usage_display);

	/** Test: util/binary. */
	test(test_bit_to_bitchar);
	test(test_bitchar_to_bit);
	test(test_bitmask_n_bits);
	test(test_bitstring_to_byte);
	test(test_byte_to_bitstring);

	/** Test: util/string. */
	test(test_char_to_int);
	test(test_string_concat);
	test(test_string_contains);
	test(test_string_equals);
	return 0;
}

int main(void) {
	info("Running tests...");
	
	all_tests();
	
	char msg[60];
	sprintf(msg, "%d/%d tests succeeded. %d assertions tested.", testunit_tests_ok, testunit_tests_total,
	        testunit_assertions);
	if (testunit_tests_ok == testunit_tests_total) {
		success(msg);
	} else {
		warning(msg);
	}
	return testunit_tests_ok != testunit_tests_total;
}

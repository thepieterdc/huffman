/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "test_unit.h"
#include "test_datastructure_huffmantree.h"
#include "test_datastructure_minheap.h"
#include "test_datastructure_queue.h"
#include "test_datatype_uint256t.h"
#include "test_io_input_bitinputstream.h"
#include "test_io_input_byteinputstream.h"
#include "test_io_input_inputstream.h"
#include "test_io_input_intinputstream.h"
#include "test_io_output_bitoutputstream.h"
#include "test_io_output_byteoutputstream.h"
#include "test_io_output_intoutputstream.h"
#include "test_io_output_outputstream.h"
#include "test_util_arguments.h"
#include "test_util_binary.h"
#include "test_util_string.h"
#include "test_datatype_huffmancode.h"
#include "test_algorithm_standard.h"

/**
 * Runs all tests.
 *
 * @return N/A
 */
static char *all_tests() {
	/** Test: algorithms/standard. */
	test(test_algorithm_standard);
	
	/** Test: datastructures/huffman_tree. */
	test(test_huffmantree_create_free_reset_counter);
	
	/** Test: datastructures/min_heap. */
	test(test_minheap_create_free);
	test(test_minheap_insert_find_extract_min);
	
	/** Test: datastructures/queue. */
	test(test_queue_create_free);
	test(test_queue_empty);
	test(test_queue_push_peek_pop);
	
	/** Test: datatypes/huffman_code. */
	test(test_huffmancode_create_left_right_free);
	
	/** Test: datatypes/uint256_t. */
	test(test_uint256t_copy);
	test(test_uint256t_create);
	test(test_uint256t_equals_is_zero);
	test(test_uint256t_nth_bit);
	test(test_uint256t_set_lsb_msb);
	test(test_uint256t_shift);
	
	/** Test: io/input/bit_input_stream. */
	test(test_io_bis_create_free);
	test(test_io_bis_read_bit_count_clear_buffer_empty);
	test(test_io_bis_read_byte_count);
	
	/** Test: io/input/byte_input_stream. */
	test(test_io_byis_create_free);
	test(test_io_byis_consume_read_count_empty);
	test(test_io_byis_feed_read_count_empty);
	
	/** Test: io/input/input_stream. */
	test(test_io_is_create_free);
	test(test_io_is_feed_read_count);
	
	/** Test: io/input/int_input_stream. */
	test(test_io_iis_create_free);
	test(test_io_iis_consume_read_count);
	test(test_io_iis_feed_read_count);
	
	/** Test: io/output/bit_output_stream. */
	test(test_io_bos_create_free);
	test(test_io_bos_feed_bit_flush_count);
	test(test_io_bos_feed_bit_pad_flush_count);
	test(test_io_bos_feed_byte_flush_count);
	
	/** Test: io/output/byte_output_stream. */
	test(test_io_byos_create_free);
	test(test_io_byos_feed_flush_count);
	
	/** Test: io/output/int_output_stream. */
	test(test_io_ios_create_free);
	test(test_io_ios_feed_flush_count);
	
	/** Test: io/output/output_stream. */
	test(test_io_os_create_free);
	test(test_io_os_feed_read_count);
	
	/** Test: util/algorithm. */
	test(test_arguments_algorithm);
	test(test_arguments_mode);
	
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
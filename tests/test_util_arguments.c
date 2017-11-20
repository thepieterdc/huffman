/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"
#include "test_util_arguments.h"
#include "../src/util/arguments.h"

const char *test_arguments_algorithm() {
	assertEquals(algorithm_from_opt('1'), STANDARD);
	assertEquals(algorithm_from_opt('2'), ADAPTIVE);
	assertEquals(algorithm_from_opt('3'), SLIDING);
	assertEquals(algorithm_from_opt('4'), TWO_PASS);
	assertEquals(algorithm_from_opt('5'), BLOCKWISE);
	return 0;
}

const char *test_arguments_mode() {
	assertEquals(mode_from_opt('c'), COMPRESS);
	assertEquals(mode_from_opt('d'), DECOMPRESS);
	return 0;
}

const char *test_arguments_usage_display() {
	char *usage;
	size_t usage_size;
	
	FILE *stream = open_memstream(&usage, &usage_size);
	usage_display(stream);
	fclose(stream);
	
	assertTrue(str_contains(usage, "-c"));
	assertTrue(str_contains(usage, "-d"));
	assertTrue(str_contains(usage, "Standard"));
	assertTrue(str_contains(usage, "Adaptive"));
	assertTrue(str_contains(usage, "sliding"));
	assertTrue(str_contains(usage, "Blockwise"));
	assertTrue(str_contains(usage, "sliding"));
	
	free(usage);
	
	return 0;
}
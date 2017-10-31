/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_unit.h"
#include "test_util_arguments.h"
#include "../src/util/arguments.h"

char *test_arguments_algorithm() {
	assertEquals(algorithm_from_opt('1'), STANDARD);
	assertEquals(algorithm_from_opt('2'), ADAPTIVE);
	assertEquals(algorithm_from_opt('3'), SLIDING);
	assertEquals(algorithm_from_opt('4'), TWO_PASS);
	assertEquals(algorithm_from_opt('5'), BLOCKWISE);
	return 0;
}

char *test_arguments_mode() {
	assertEquals(mode_from_opt('c'), COMPRESS);
	assertEquals(mode_from_opt('d'), DECOMPRESS);
	return 0;
}
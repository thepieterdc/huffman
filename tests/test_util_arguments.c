/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_unit.h"
#include "test_util_arguments.h"
#include "../src/util/arguments.h"

char *test_arguments_algorithm() {
	assertThat(algorithm_from_opt('1') == STANDARD);
	assertThat(algorithm_from_opt('2') == ADAPTIVE);
	assertThat(algorithm_from_opt('3') == ADAPTIVE_SLIDING);
	assertThat(algorithm_from_opt('4') == TWO_PASS);
	assertThat(algorithm_from_opt('5') == BLOCKWISE);
	return 0;
}

char *test_arguments_mode() {
	assertThat(mode_from_opt('c') == COMPRESS);
	assertThat(mode_from_opt('d') == DECOMPRESS);
	return 0;
}
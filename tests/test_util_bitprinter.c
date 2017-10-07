/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_unit.h"

#include "test_util_bitprinter.h"
#include "../src/util/bitprinter.h"

char *test_bitprinter_create_free() {
	bitprinter *bp = bitprinter_create(stdout);
	assertThat(bp != NULL);
	bitprinter_free(bp, false);
	return 0;
}
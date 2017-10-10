/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"

#include "test_util_bitstream.h"
#include "../src/util/bitstream.h"
#include "../src/util/string.h"

char *test_bs_create_free() {
	bitstream *bs = bs_create();
	assertThat(bs != NULL);
	bs_free(bs);
	return 0;
}
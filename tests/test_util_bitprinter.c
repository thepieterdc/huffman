/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_unit.h"

#include "test_util_bitprinter.h"
#include "../src/util/bitprinter.h"
#include "../src/util/string.h"

char *test_bitprinter_create_free() {
	bitprinter *bp = bitprinter_create(NULL);
	assertThat(bp != NULL);
	bitprinter_free(bp, false);
	return 0;
}

char *test_bitprinter_add_bit() {
	string buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	bitprinter *bp = bitprinter_create(memfile);
	assertThat(bp != NULL);
	
	/* Ascii code for the letter A (65). */
	bitprinter_add_bit(bp, false);
	bitprinter_add_bit(bp, true);
	bitprinter_add_bit(bp, false);
	bitprinter_add_bit(bp, false);
	bitprinter_add_bit(bp, false);
	bitprinter_add_bit(bp, false);
	bitprinter_add_bit(bp, false);
	bitprinter_add_bit(bp, true);
	bitprinter_flush(bp);
	
	assertThat(strequals(buf, "A"));
	assertThat(bp->cursor == 0);
	assertThat(bp->buffer == 0);
	
	fclose(memfile);
	
	bitprinter_free(bp, false);
	return 0;
}
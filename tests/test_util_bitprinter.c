/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"

#include "test_util_bitprinter.h"
#include "../src/util/bitprinter.h"
#include "../src/util/string.h"

char *test_bp_create_free() {
	bitprinter *bp = bp_create(NULL);
	assertThat(bp != NULL);
	bp_free(bp, false);
	return 0;
}

char *test_bp_print_bit() {
	string buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	bitprinter *bp = bp_create(memfile);
	assertThat(bp != NULL);
	
	/* Ascii code for the letter A (65). */
	bp_print_bit(bp, false);
	bp_print_bit(bp, true);
	bp_print_bit(bp, false);
	bp_print_bit(bp, false);
	bp_print_bit(bp, false);
	bp_print_bit(bp, false);
	bp_print_bit(bp, false);
	bp_print_bit(bp, true);
	
	assertThat(strequals(buf, "A"));
	assertThat(bp->cursor == 0);
	assertThat(bp->buffer == 0);
	
	fclose(memfile);
	free(buf);
	
	bp_free(bp, false);
	return 0;
}

char *test_bp_print_bitstring() {
	string buf;
	size_t size;
	FILE *memfile = open_memstream(&buf, &size);
	
	bitprinter *bp = bp_create(memfile);
	assertThat(bp != NULL);
	
	/* Ascii code for the letter A (65). */
	bp_print_bitstring(bp, "01000001");
	
	assertThat(strequals(buf, "A"));
	assertThat(bp->cursor == 0);
	assertThat(bp->buffer == 0);
	
	fclose(memfile);
	free(buf);
	
	bp_free(bp, false);
	return 0;
}
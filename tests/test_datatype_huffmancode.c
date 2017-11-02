/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_datatype_huffmancode.h"
#include "test_unit.h"
#include "../src/datatypes/huffman_code.h"

const char *test_huffmancode_create_left_right() {
	huffman_code *code = huffmancode_create();
	assertNotNull(code);
	
	huffman_code *left = huffmancode_create_left(code);
	assertNotNull(left);
	assertEquals(left->code, 0);
	
	huffman_code *right = huffmancode_create_right(code);
	assertNotNull(right);
	assertEquals(right->code, 1);
	
	free(code);
	free(left);
	free(right);
	
	return 0;
}
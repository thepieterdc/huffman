/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datatype_huffmancode.h"
#include "test_unit.h"
#include "../src/datatypes/huffman_code.h"

char *test_huffmancode_create_left_right_free() {
	huffman_code *code = huffmancode_create(1);
	assertThat(code != NULL);
	
	huffman_code *left = huffmancode_create_left(code);
	assertThat(left != NULL);
	assertThat(left->code->value[3] == 2);
	
	huffman_code *right = huffmancode_create_right(code);
	assertThat(right != NULL);
	assertThat(right->code->value[3] == 3);
	
	huffmancode_free(code);
	huffmancode_free(left);
	huffmancode_free(right);
	
	return 0;
}
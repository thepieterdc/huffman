/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_datatype_huffmancode.h"
#include "test_unit.h"
#include "../src/datatypes/huffman_code.h"

char *test_huffmancode_create_left_right_free() {
	huffman_code *code = huffmancode_create();
	assertThat(code != NULL);
	
	huffman_code *left = huffmancode_create_left(code);
	assertThat(left != NULL);
	assertThat(left->code == 0);
	
	huffman_code *right = huffmancode_create_right(code);
	assertThat(right != NULL);
	assertThat(right->code == 1);
	
	free(code);
	free(left);
	free(right);
	
	return 0;
}
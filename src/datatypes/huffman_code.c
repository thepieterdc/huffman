/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_code.h"
#include "../util/memory.h"

huffman_code *huffmancode_create() {
	huffman_code *ret = (huffman_code *) mallocate(sizeof(huffman_code));
	ret->code = uint256(0);
	ret->padding = 0;
	return ret;
}

huffman_code *huffmancode_create_left(huffman_code *parent) {
	huffman_code *ret = (huffman_code *) mallocate(sizeof(huffman_code));
	ret->code = uint256_shift_left_assign(uint256_copy(parent->code));
	ret->padding = parent->padding + uint256_is_zero(ret->code);
	return ret;
}

huffman_code *huffmancode_create_right(huffman_code *parent) {
	huffman_code *ret = (huffman_code *) mallocate(sizeof(huffman_code));
	ret->code = uint256_shift_left_assign(uint256_copy(parent->code));
	uint256_set_lsb(ret->code, 1);
	ret->padding = parent->padding;
	return ret;
}

void huffmancode_free(huffman_code *code) {
	free(code->code);
	free(code);
}
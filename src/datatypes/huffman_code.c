/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_code.h"
#include "../util/logging.h"
#include "../util/errors.h"

huffman_code *huffmancode_create(bit start) {
	huffman_code *ret = (huffman_code *) malloc(sizeof(huffman_code));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->code = uint256((uint64_t) start);
		ret->padding = 0;
	}
	return ret;
}

huffman_code *huffmancode_create_left(huffman_code *parent) {
	huffman_code *ret = (huffman_code *) malloc(sizeof(huffman_code));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->code = uint256_shift_left_assign(uint256_copy(parent->code));
		ret->padding = parent->padding + uint256_is_zero(ret->code);
	}
	return ret;
}

huffman_code *huffmancode_create_right(huffman_code *parent) {
	huffman_code *ret = (huffman_code *) malloc(sizeof(huffman_code));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->code = uint256_shift_left_assign(uint256_copy(parent->code));
		uint256_set_lsb(ret->code, 1);
		ret->padding = parent->padding;
	}
	return ret;
}

void huffmancode_free(huffman_code *code) {
	free(code->code);
	free(code);
}
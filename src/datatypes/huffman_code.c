/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_code.h"
#include "../util/memory.h"

huffman_code *huffmancode_create() {
	return (huffman_code *) callocate(1, sizeof(huffman_code));
}

huffman_code *huffmancode_create_left(huffman_code *parent) {
	huffman_code *ret = (huffman_code *) mallocate(sizeof(huffman_code));
	ret->code = parent->code << 1;
	ret->length = (uint_fast8_t) (parent->length + 1);
	return ret;
}

huffman_code *huffmancode_create_right(huffman_code *parent) {
	huffman_code *ret = (huffman_code *) mallocate(sizeof(huffman_code));
	ret->code = (parent->code << 1) | 1;
	ret->length = (uint_fast8_t) (parent->length + 1);
	return ret;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_tree.h"
#include "../util/logging.h"
#include "../util/errors.h"

huffman_node *huffman_create_leaf(byte data, uint8_t weight) {
	huffman_node *ret = (huffman_node *) malloc(sizeof(huffman_node));
	if(!ret) {
		error(ERROR_MALLOC_FAILED);
	}
	
	return ret;
}
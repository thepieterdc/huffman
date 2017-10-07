/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_HUFFMAN_TREE_H
#define HUFFMAN_UTIL_HUFFMAN_TREE_H

#include <unistd.h>

typedef struct {
	int code;
	char value;
	size_t weight;
} huffman_node;

#endif /* HUFFMAN_UTIL_HUFFMAN_TREE_H */

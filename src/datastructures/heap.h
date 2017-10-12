/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */


#ifndef HUFFMAN_DATASTRUCTURES_HEAP_H
#define HUFFMAN_DATASTRUCTURES_HEAP_H

#include <unistd.h>

/**
 * A node in the heap.
 */
typedef struct heap_node {
	void *data;
	size_t key;
} heap_node;

#endif /*HUFFMAN_DATASTRUCTURES_HEAP_H */

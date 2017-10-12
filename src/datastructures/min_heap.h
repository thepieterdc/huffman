/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_MIN_HEAP_H
#define HUFFMAN_DATASTRUCTURES_MIN_HEAP_H

#include "heap.h"

/**
 * A min-heap.
 */
typedef struct min_heap {
	heap_node **heap;
	size_t maxsize;
	size_t size;
} min_heap;

/**
 * Creates a new min-heap.
 *
 * @param maxsize the maximum amount of items in the heap
 * @return the created min-heap
 */
min_heap *minheap_create(size_t maxsize);

/**
 * Removes the element with the lowest key in the min-heap.
 *
 * @param heap the min-heap
 * @return the element with the lowest key
 */
void *minheap_extract_min(min_heap *heap);

/**
 * Gets the element with the lowest key in the min-heap.
 *
 * @param heap the min-heap
 * @return the element with the lowest key
 */
void *minheap_find_min(min_heap *heap);

/**
 * Frees the memory allocated by the min-heap.
 *
 * @param heap the min-heap
 */
void minheap_free(min_heap *heap);

/**
 * Inserts an item in the min-heap.
 *
 * @param heap the min-heap
 * @param key the key of the item to insert
 * @param data the item to insert
 */
void minheap_insert(min_heap *heap, size_t key, void *data);

#endif /* HUFFMAN_DATASTRUCTURES_MIN_HEAP_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "min_heap.h"
#include "../util/logging.h"
#include "../util/errors.h"

#include <stdio.h>

/**
 * Gets the position of this node's left child.
 *
 * @param p the current node
 * @return the position of the left node
 */
#define heap_left(p) (2*(p) + 1)

/**
 * Gets the position of this node's parent node.
 *
 * @param p the current node
 * @return the position of the parent node
 */
#define heap_parent(p) (((p) - 1)/2)

/**
 * Gets the position of this node's right child.
 *
 * @param p the current node
 * @return the position of the right node
 */
#define heap_right(p) (2*(p) + 2)

/**
 * Maintains the min-heap property.
 *
 * @param heap the minheap
 * @param position the position to start (recursive)
 */
static void min_heapify(min_heap *heap) {
	int index = 0;
	int left = heap_left(index);
	int right = heap_right(index);
	
	while (index < heap->size) {
		int swap = index;
		
		if (left < heap->size && heap->heap[left]->key < heap->heap[index]->key) {
			swap = left;
		}
		
		if (right < heap->size && heap->heap[right]->key < heap->heap[swap]->key) {
			swap = right;
		}
		
		if (index != swap) {
			heap_node *tmp = heap->heap[index];
			heap->heap[index] = heap->heap[swap];
			heap->heap[swap] = tmp;
			
			index = swap;
			left = heap_left(index);
			right = heap_right(index);
		} else {
			break;
		}
	}
}

min_heap *minheap_create(size_t maxsize) {
	min_heap *heap = (min_heap *) malloc(sizeof(min_heap));
	if (!heap) {
		error(ERROR_MALLOC_FAILED);
	} else {
		heap->heap = (heap_node **) calloc(sizeof(heap_node *), maxsize);
		heap->maxsize = maxsize;
		heap->size = 0;
	}
	
	return heap;
}

void *minheap_extract_min(min_heap *heap) {
	if (heap->size == 0) {
		error(ERROR_EMPTY_HEAP);
	}
	
	void *min = heap->heap[0]->data;
	
	free(heap->heap[0]);
	
	heap->heap[0] = heap->heap[--heap->size];
	
	min_heapify(heap);
	
	return min;
}

void *minheap_find_min(min_heap *heap) {
	if (heap->size == 0) {
		error(ERROR_EMPTY_HEAP);
	}
	return heap->heap[0]->data;
}

void minheap_free(min_heap *heap) {
	for (size_t i = 0; i < heap->size; ++i) {
		free(heap->heap[i]);
	}
	free(heap->heap);
	free(heap);
}

void minheap_insert(min_heap *heap, size_t key, void *data) {
	if (heap->size == heap->maxsize) {
		error(ERROR_INDEX_OUT_OF_BOUNDS);
	}
	
	heap_node *node = (heap_node *) malloc(sizeof(heap_node));
	node->key = key;
	node->data = data;
	heap->heap[heap->size++] = node;
	
	int index = (int) (heap->size - 1);
	int parent = heap_parent(index);
	while (index > 0 && heap->heap[index]->key < heap->heap[parent]->key) {
		heap_node *tmp = heap->heap[index];
		heap->heap[index] = heap->heap[parent];
		heap->heap[parent] = tmp;
		
		index = parent;
		parent = heap_parent(index);
	}
}
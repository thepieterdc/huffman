/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datastructure_minheap.h"
#include "test_unit.h"
#include "../src/datastructures/min_heap.h"

#include <stdio.h>

char *test_minheap_create_free() {
	min_heap *heap = minheap_create(2);
	assertThat(heap != NULL);
	assertThat(heap->heap != NULL);
	assertThat(heap->maxsize == 2);
	minheap_free(heap);
	return 0;
}

char *test_minheap_insert_find_extract_min() {
	min_heap *heap = minheap_create(5);
	assertThat(heap != NULL);
	
	minheap_insert(heap, 4, (void *) 'A');
	minheap_insert(heap, 3, (void *) 'B');
	minheap_insert(heap, 2, (void *) 'C');
	minheap_insert(heap, 5, (void *) 'D');
	minheap_insert(heap, 1, (void *) 'E');
	assertThat(heap->size == 5);
	
	char testcases[5] = {'E', 'C', 'B', 'A', 'D'};
	
	for (size_t i = 0; i < 5; ++i) {
		printf("%c - %c\n", (unsigned char) minheap_find_min(heap), testcases[i]);
		assertThat((char) minheap_find_min(heap) == testcases[i]);
		assertThat((char) minheap_extract_min(heap) == testcases[i]);
		assertThat(heap->size == 5 - 1 - i);
//
//		for(size_t j = 0; j < heap->size; ++j) {
//			printf("%c - ", (unsigned char) heap->heap[j]->data);
//		}
//		printf("\n");
	}
	
	minheap_free(heap);
	
	return 0;
}
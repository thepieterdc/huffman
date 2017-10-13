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
	min_heap *heap = minheap_create(8);
	assertThat(heap != NULL);
	
	minheap_insert(heap, 4, (void *) 'A');
	minheap_insert(heap, 3, (void *) 'B');
	minheap_insert(heap, 5, (void *) 'C');
	minheap_insert(heap, 8, (void *) 'D');
	minheap_insert(heap, 1, (void *) 'E');
	minheap_insert(heap, 7, (void *) 'F');
	minheap_insert(heap, 6, (void *) 'G');
	minheap_insert(heap, 2, (void *) 'H');
	assertThat(heap->size == 8);
	
	char testcases[8] = {'E', 'H', 'B', 'A', 'C', 'G', 'F', 'D'};
	
	for (size_t i = 0; i < 8; ++i) {
		
		printf("%c - %c\n", (unsigned char) minheap_find_min(heap), testcases[i]);
		assertThat((char) minheap_find_min(heap) == testcases[i]);
		assertThat((char) minheap_extract_min(heap) == testcases[i]);
		assertThat(heap->size == 8 - 1 - i);
	}
	
	minheap_free(heap);
	
	return 0;
}
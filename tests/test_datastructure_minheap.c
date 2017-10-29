/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datastructure_minheap.h"
#include "test_unit.h"
#include "../src/datastructures/min_heap.h"
#include "../src/datatypes/bit.h"

#include <stdio.h>
#include <stdint.h>

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
	
	byte originals[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	
	minheap_insert(heap, 4, (void *) &originals[0]);
	minheap_insert(heap, 3, (void *) &originals[1]);
	minheap_insert(heap, 5, (void *) &originals[2]);
	minheap_insert(heap, 8, (void *) &originals[3]);
	minheap_insert(heap, 1, (void *) &originals[4]);
	minheap_insert(heap, 7, (void *) &originals[5]);
	minheap_insert(heap, 6, (void *) &originals[6]);
	minheap_insert(heap, 2, (void *) &originals[7]);
	assertThat(heap->size == 8);
	
	byte testcases[8] = {'E', 'H', 'B', 'A', 'C', 'G', 'F', 'D'};
	
	byte *find_min;
	byte *extract_min;
	for (size_t i = 0; i < 8; ++i) {
		find_min = (byte *) minheap_find_min(heap);
		extract_min = (byte *) minheap_extract_min(heap);
		assertThat(*find_min == testcases[i]);
		assertThat(*extract_min == testcases[i]);
		assertThat(heap->size == 8 - 1 - i);
	}
	
	minheap_free(heap);
	
	return 0;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "datastructures/dynamic_array.h"
#include "datastructures/huffman_tree.h"

int main(void) {
	//Bevat ascii waarden van de letters
	int *frequencies = (int *) malloc(255 * sizeof(int));
	
	int in;
	while ((in = (char) getchar()) > -1) {
		frequencies[in]++;
	}
	
	dynamic_array *heap = da_create();
	for (int i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			huffman_node *node = (huffman_node *) malloc(sizeof(huffman_node));
			node->type = LEAF;
			node->left = NULL;
			node->right = NULL;
			node->value = (char) i;
			node->weight = (size_t) frequencies[i];
			da_add(heap, node);
		}
	}
	
	while (heap->size > 1) {
		huffman_node *minnode1 = da_get(heap, 0);
		int minnode1_idx = 0;
		for (int i = 1; i < heap->size; ++i) {
			huffman_node *node = da_get(heap, (size_t) i);
			if (node->weight < minnode1->weight) {
				minnode1 = node;
				minnode1_idx = i;
			}
		}
		da_remove_index(heap, (size_t) minnode1_idx);
		
		huffman_node *minnode2 = da_get(heap, 0);
		int minnode2_idx = 0;
		for (int i = 1; i < heap->size; ++i) {
			huffman_node *node = da_get(heap, (size_t) i);
			if (node->weight < minnode2->weight) {
				minnode2 = node;
				minnode2_idx = i;
			}
		}
		da_remove_index(heap, (size_t) minnode2_idx);
		
		huffman_node *node = (huffman_node *) malloc(sizeof(huffman_node));
		node->type = NODE;
		node->left = minnode1;
		node->right = minnode2;
		node->weight = minnode1->weight + minnode2->weight;
		da_add(heap, node);
	}
	
	printf("%d\n", (int) heap->size);
	
	return 0;
}
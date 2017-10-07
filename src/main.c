/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "datastructures/dynamic_array.h"
#include "datastructures/huffman_tree.h"

//Returns the amount of characters printed, sets the codes
//printcodes = array containing all the codes in order of generation to
int print_tree_update_codes(huffman_node *tree, char *currentcode, char **codes, dynamic_array *printcodes) {
	if (tree->type == LEAF) {
		printf("1");
		codes[tree->value] = currentcode;
		da_add(printcodes, currentcode);
		return 1;
	} else {
		printf("0");
		char *leftcode = (char *) malloc(strlen(currentcode) + 2);
		char *rightcode = (char *) malloc(strlen(currentcode) + 2);
		sprintf(leftcode, "%s0", currentcode);
		sprintf(rightcode, "%s1", currentcode);
		return 1 + print_tree_update_codes(tree->left, leftcode, codes, printcodes) +
		       print_tree_update_codes(tree->right, rightcode, codes, printcodes);
	}
}

int main(void) {
	//Bevat ascii waarden van de letters
	dynamic_array *raw_string = da_create();
	int *frequencies = (int *) malloc(256 * sizeof(int));
	
	int in;
	while ((in = getchar()) > -1) {
		frequencies[in]++;
		da_add(raw_string, (void *) in);
	}
	
	dynamic_array *heap = da_create();
	for (int i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			huffman_node *node = (huffman_node *) malloc(sizeof(huffman_node));
			node->type = LEAF;
			node->left = NULL;
			node->right = NULL;
			node->value = i;
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
	
	huffman_node *tree = da_get(heap, 0);
	
	char **codes_dictionary = (char **) malloc(256 * sizeof(char *));
	dynamic_array *volgorde_codes = da_create();
	
	// Print tree
	int amt_printed = print_tree_update_codes(tree, "0\0", codes_dictionary, volgorde_codes);
	if (amt_printed % 8 != 0) {
		for (size_t i = (size_t) amt_printed; i < 8; ++i) {
			printf("0");
		}
	}
	fflush(stdout);
	
	// Print letters DFS based
	for (int i = 0; i < volgorde_codes->size; ++i) {
		printf("%s", (char *) da_get(volgorde_codes, (size_t) i));
	}
	fflush(stdout);
	
	// Print encoded word
	for (int i = 0; i < raw_string->size; ++i) {
		printf("%s", codes_dictionary[(int) da_get(raw_string, (size_t) i)]);
	}
	
	fflush(stdout);
	return 0;
}
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
#include "util/bitprinter.h"

int build_tree(huffman_node *tree, char *currentcode, dynamic_array *order_codes) {
	char c = (char) getchar();
	if (c == '1') {
		tree->type = LEAF;
		da_add(order_codes, currentcode);
		return 1;
	} else {
		tree->type = NODE;
		
		huffman_node *leftnode = malloc(sizeof(huffman_node));
		huffman_node *rightnode = malloc(sizeof(huffman_node));
		tree->left = leftnode;
		tree->right = rightnode;
		
		char *leftcode = (char *) malloc(strlen(currentcode) + 2);
		char *rightcode = (char *) malloc(strlen(currentcode) + 2);
		sprintf(leftcode, "%s0", currentcode);
		sprintf(rightcode, "%s1", currentcode);
		return 1 + build_tree(leftnode, leftcode, order_codes) + build_tree(rightnode, rightcode, order_codes);
	}
}

int main(void) {
	dynamic_array *volgorde_codes = da_create();
	
	/** Boom opbouwen */
	huffman_node *tree = malloc(sizeof(huffman_node));
	int bitsread = build_tree(tree, "\0", volgorde_codes);
	
	/* Padding */
	while (bitsread % 8 != 0) {
		getchar();
		bitsread++;
	}
	
	/** Codes lezen en mappen. */
	size_t amtcodes = volgorde_codes->size;
	for (int i = 0; i < amtcodes; ++i) {
		char *code = da_get(volgorde_codes, (size_t) i);
		huffman_node *cursor = tree;
		for(int j = 0; j < strlen(code); ++j) {
			if(code[j] == '1') {
				cursor = cursor->right;
			} else {
				cursor = cursor->left;
			}
		}
		cursor->value = getchar();
	}

	int c;
	huffman_node *cursor = tree;

	while ((c = getchar()) > -1) {
		char ch = (char) c;

		if (ch == '1') {
			cursor = cursor->right;
		} else {
			cursor = cursor->left;
		}

		if (cursor->type == LEAF) {
			printf("%c", (char) cursor->value);
			cursor = tree;
		}
	}
	return 0;
}
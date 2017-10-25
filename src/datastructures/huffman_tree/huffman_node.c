/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_node.h"
#include "../../util/memory.h"
#include "adaptive_huffman_tree.h"

huffman_node *huffmannode_create_leaf(byte data, size_t weight) {
	huffman_node *ret = (huffman_node *) callocate(1, sizeof(huffman_node));
	ret->data = data;
	ret->type = LEAF;
	ret->weight = weight;
	return ret;
}

huffman_node *huffmannode_create_node(huffman_node *left, huffman_node *right) {
	huffman_node *ret = (huffman_node *) callocate(1, sizeof(huffman_node));
	ret->type = NODE;
	
	ret->left = left;
	ret->right = right;
	if (left) {
		ret->weight += left->weight;
		left->parent = ret;
	}
	if (right) {
		ret->weight += right->weight;
		right->parent = ret;
	}
	return ret;
}

huffman_node *huffmannode_create_nyt() {
	huffman_node *ret = (huffman_node *) callocate(1, sizeof(huffman_node));
	ret->type = NYT;
	ret->weight = 0;
	return ret;
}

void huffmannode_free(huffman_node *node) {
	if (node->code != NULL) {
		huffmancode_free(node->code);
	}
	if (node->left != NULL) {
		huffmannode_free(node->left);
	}
	if (node->right != NULL) {
		huffmannode_free(node->right);
	}
	free(node);
}
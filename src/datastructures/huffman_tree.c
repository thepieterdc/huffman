/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_tree.h"
#include "../util/logging.h"
#include "../util/errors.h"

huffman_node *huffman_create_leaf(byte data, size_t weight) {
	huffman_node *ret = (huffman_node *) malloc(sizeof(huffman_node));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->order_no = 0;
		ret->type = LEAF;
		ret->code = NULL;
		ret->left = NULL;
		ret->right = NULL;
		ret->data = data;
		ret->weight = weight;
	}
	return ret;
}

huffman_node *huffman_create_node(huffman_node *left, huffman_node *right) {
	huffman_node *ret = (huffman_node *) malloc(sizeof(huffman_node));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->order_no = 0;
		ret->type = NODE;
		ret->code = NULL;
		ret->left = left;
		ret->right = right;
		ret->data = 0;
		ret->weight = 0;
		if (left != NULL) {
			ret->weight += left->weight;
		}
		if (right != NULL) {
			ret->weight += right->weight;
		}
	}
	return ret;
}

void huffman_free(huffman_node *node) {
	if (node->code != NULL) {
		huffmancode_free(node->code);
	}
	if (node->left != NULL) {
		huffman_free(node->left);
	}
	if (node->right != NULL) {
		huffman_free(node->right);
	}
	free(node);
}

/**
 * Recursive step to print a Huffman tree.
 *
 * @param root the root of the subtree
 * @param indent the identation level
 */
static void huffman_print_tree_rec(huffman_node *root, uint_fast16_t indent) {
	for (size_t i = 0; i < indent; ++i) {
		fprintf(stderr, "\t");
	}
	if (root->type == LEAF) {
		fprintf(stderr, "LEAF[o=%ld, a=%ld, data=%d]", root->order_no, root->weight, root->data);
	} else {
		fprintf(stderr, "NODE[o=%ld, a=%ld]", root->order_no, root->weight);
		huffman_print_tree_rec(root->left, indent + 1);
		huffman_print_tree_rec(root->right, indent + 1);
	}
	
}

void huffman_print_tree(huffman_node *root) {
	fprintf(stderr, "ROOT[o=%ld, a=%ld\n]", root->order_no, root->weight);
	
	if (root->left != NULL) {
		huffman_print_tree_rec(root->left, 1);
	}
	if (root->right != NULL) {
		huffman_print_tree_rec(root->right, 1);
	}
}
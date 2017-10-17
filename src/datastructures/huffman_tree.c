/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "huffman_tree.h"
#include "../util/logging.h"
#include "../util/errors.h"

/**
 * Counts order numbers.
 */
static uint8_t node_counter = 0;

huffman_node *huffman_create_leaf(byte data, size_t weight) {
	huffman_node *ret = (huffman_node *) malloc(sizeof(huffman_node));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->order_no = node_counter++;
		ret->type = LEAF;
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
		ret->order_no = node_counter++;
		ret->type = NODE;
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
	if (node->code) {
		huffmancode_free(node->code);
	}
	if (node->left) {
		huffman_free(node->left);
	}
	if (node->right) {
		huffman_free(node->right);
	}
	free(node);
}

void huffman_print_tree(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		bos_feed_bit(out, 1);
	} else {
		bos_feed_bit(out, 0);
		
		huffman_print_tree(root->left, out);
		huffman_print_tree(root->right, out);
	}
}

void huffman_reset_ordercounter() {
	node_counter = 0;
}
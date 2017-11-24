/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "twopass.h"
#include "../../datastructures/byte_queue.h"
#include "../../util/binary.h"
#include "../../io/output/bit_output_stream.h"

void twopass_assign_weights(huffman_node *root, bit_input_stream *in) {
	if (root->type == LEAF) {
		root->weight = bis_read_byte(in) << 24;
		root->weight |= (bis_read_byte(in) << 16);
		root->weight |= (bis_read_byte(in) << 8);
		root->weight |= bis_read_byte(in);
	} else {
		twopass_assign_weights(root->left, in);
		twopass_assign_weights(root->right, in);
		root->weight = root->left->weight + root->right->weight;
	}
}

byte twopass_decode_character(huffman_tree *tree, bit_input_stream *in, FILE *out) {
	huffman_node *cursor = tree->root;
	
	while (cursor->type != NYT && cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	putc_unlocked(cursor->data, out);
	return cursor->data;
}

void twopass_parse_tree(adaptive_huffman_tree *aht, huffman_tree *tree) {
	aht->tree = tree;
	
	/* Set the order numbers using Breadth First Search. */
	huffman_node *queue[HUFFMAN_MAX_NODES];
	queue[0] = tree->root;
	
	size_t cursor = 0;
	size_t max = 1;
	while (cursor < max) {
		aht->nodes[cursor] = queue[cursor];
		aht->nodes[cursor]->order_no = (uint_least16_t) cursor;
		
		if (queue[cursor]->type == NODE) {
			queue[max++] = queue[cursor]->right;
			queue[max++] = queue[cursor]->left;
		}
		
		++cursor;
	}
	
	/* Create an NYT node. */
	aht->nyt = huffmannode_create_nyt();
	aht->nyt->order_no = HUFFMAN_MAX_NODES - 1;
	aht->nodes[HUFFMAN_MAX_NODES - 1] = aht->nyt;
	
	/* Add the NYT node to the tree. */
	huffman_node *original_parent = aht->nodes[cursor - 1]->parent;
	huffman_node *parent = huffmannode_create_node(aht->nyt, aht->nodes[cursor - 1]);
	
	parent->parent = original_parent;
	if (original_parent->left == aht->nodes[cursor - 1]) {
		original_parent->left = parent;
	} else {
		original_parent->right = parent;
	}
	
	parent->order_no = aht->nodes[cursor - 1]->order_no;
	aht->nodes[cursor - 1]->order_no++;
	
	aht->nodes[cursor - 1] = parent;
	aht->nodes[cursor] = parent->right;
	aht->amt_nodes = (uint_least16_t) (max + 1);
}

void twopass_print_weights(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		putc_unlocked((byte) ((root->weight >> 24) & BYTE_MASK), out->channel);
		putc_unlocked((byte) ((root->weight >> 16) & BYTE_MASK), out->channel);
		putc_unlocked((byte) ((root->weight >> 8) & BYTE_MASK), out->channel);
		putc_unlocked((byte) (root->weight & BYTE_MASK), out->channel);
	} else {
		twopass_print_weights(root->left, out);
		twopass_print_weights(root->right, out);
	}
}
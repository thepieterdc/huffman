/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "twopass.h"
#include "../../datastructures/byte_queue.h"

byte twopass_decode_character(huffman_tree *tree, bit_input_stream *in, FILE *out) {
	huffman_node *cursor = tree->root;
	
	while (cursor->type != NYT && cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	putc(cursor->data, out);
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
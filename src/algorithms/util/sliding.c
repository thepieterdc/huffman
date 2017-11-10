/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "sliding.h"
#include "../../util/logging.h"
#include "adaptive.h"
#include "../../datastructures/byte_queue.h"

huffman_node *
sliding_decode_character(adaptive_huffman_tree *tree, byte_queue *window, bit_input_stream *in, FILE *out) {
	huffman_node *cursor = tree->tree->root;
	
	while (cursor->type != NYT && cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	
	if (cursor->type == NYT) {
		/* z is a new character; add it to the tree. */
		byte z = bis_read_byte(in);
		huffman_node *o = adaptive_add_character(tree, z);
		putc(z, out);
		byte_queue_push(window, z);
		return o->parent;
	} else {
		putc(cursor->data, out);
		byte_queue_push(window, cursor->data);
		return cursor;
	}
}

uint_least16_t sliding_find_swap(adaptive_huffman_tree *tree, uint_least64_t weight) {
	for (uint_least16_t i = tree->amt_nodes; i > 0; --i) {
		if (tree->nodes[i - 1]->weight == weight) {
			return (uint_least16_t) (i - 1);
		}
	}
	return 0;
}

void sliding_remove_node(adaptive_huffman_tree *tree, huffman_node *node) {
	huffman_node *parent = tree->nyt->parent;
	huffman_node *remove_node = parent->right;
	
	tree->nyt->parent = parent->parent;
	if (parent->parent->left == parent) {
		parent->parent->left = tree->nyt;
	} else {
		parent->parent->right = tree->nyt;
	}
	
	parent->left = NULL;
	parent->right = NULL;
	
	tree->nodes[parent->order_no] = tree->nyt;
	tree->nyt->order_no = parent->order_no;
	tree->nyt->weight = 1;
	
	huffmannode_free(parent);
	huffmannode_free(remove_node);
	
	tree->amt_nodes--;
	
	huffman_node *t = tree->nyt;
	huffman_node *swap_node;
	while (t->parent) {
		swap_node = tree->nodes[sliding_find_swap(tree, t->weight)];
		if (t != swap_node && swap_node->parent != t && t->parent != swap_node) {
			/* Swap the nodes in the tree. */
			adaptive_do_swap(tree, t, swap_node);
		}
		t = t->parent;
	}
	
	tree->nodes[tree->nyt->order_no] = NULL;
	tree->amt_nodes--;
	
	tree->nyt->weight = 0;
	tree->nyt->order_no = HUFFMAN_MAX_NODES - 1;
}

void sliding_update_tree(adaptive_huffman_tree *tree, byte b) {
	huffman_node *t = tree->tree->leaves[b];
	huffman_node *swap_node;
	
	/* Remove the node from the tree. */
	bool remove = t->weight == 1;
	
	while (t->parent) {
		swap_node = tree->nodes[sliding_find_swap(tree, t->weight)];
		if (t != swap_node && swap_node->parent != t && t->parent != swap_node) {
			/* Swap the nodes in the tree. */
			adaptive_do_swap(tree, t, swap_node);
		}
		t->weight--;
		t = t->parent;
	}
	t->weight--;
	
	if (remove) {
		sliding_remove_node(tree, tree->tree->leaves[b]);
		tree->tree->leaves[b] = NULL;
	}
}
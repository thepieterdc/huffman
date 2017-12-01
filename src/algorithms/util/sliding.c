/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include "sliding.h"
#include "adaptive.h"

huffman_node *
sliding_decode_character(adaptive_huffman_tree *tree, byte_queue *window, bit_input_stream *in, FILE *out) {
	huffman_node *cursor = tree->tree->root;
	
	/* Traverse through the tree to process the input code. */
	while (cursor->type != NYT && cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = huffmantree_traverse(cursor, rd);
	}
	
	if (cursor->type == NYT) {
		/* z is a new character; add it to the tree. */
		byte z = bis_read_byte(in);
		huffman_node *o = adaptive_add_character(tree, z);
		/* Print the new character. */
		putc_unlocked(z, out);
		/* Add the character to the sliding window. */
		byte_queue_push(window, z);
		return o->parent;
	} else {
		/* Print an existing character. */
		putc_unlocked(cursor->data, out);
		/* Add the character to the sliding window. */
		byte_queue_push(window, cursor->data);
		return cursor;
	}
}

uint_least16_t sliding_find_swap(adaptive_huffman_tree *tree, huffman_node *node) {
	register uint_fast64_t weight = node->weight;
	for (uint_least16_t i = (uint_least16_t) (node->order_no + 1); i < tree->amt_nodes; ++i) {
		if (tree->nodes[i]->weight != weight) {
			return (uint_least16_t) (i - 1);
		}
	}
	
	return (uint_least16_t) (tree->amt_nodes - 1);
}

void sliding_remove_node(adaptive_huffman_tree *tree) {
	huffman_node *parent = tree->nyt->parent;
	huffman_node *remove_node = parent->right;
	
	tree->nyt->parent = parent->parent;
	
	/* Replace the parent with the NYT node. */
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
	
	/* Free the memory allocated by the now detached nodes. */
	huffmannode_free(parent);
	huffmannode_free(remove_node);
	
	/* Decrease the amount of nodes. */
	tree->amt_nodes--;
	
	/* Make sure the NYT node is the sibling of the highest order number. */
	huffman_node *t = tree->nyt;
	huffman_node *swap_node;
	while (t->parent) {
		/* Find the node with the highest order number and same weight as t. */
		swap_node = tree->nodes[sliding_find_swap(tree, t)];
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
	
	if (tree->nyt->parent->order_no != tree->amt_nodes - 2) {
		adaptive_do_swap(tree, tree->nyt->parent, tree->nodes[tree->amt_nodes - 2]);
	}
}

void sliding_update_tree(adaptive_huffman_tree *tree, byte b) {
	huffman_node *t = tree->tree->leaves[b];
	huffman_node *swap_node;
	
	/* Remove the node from the tree. */
	bool remove = t->weight == 1;
	
	while (t->parent) {
		/* Find the node with the highest order number and same weight as t. */
		swap_node = tree->nodes[sliding_find_swap(tree, t)];
		if (t != swap_node && swap_node->parent != t) {
			/* Swap the nodes in the tree. */
			adaptive_do_swap(tree, t, swap_node);
		}
		t->weight--;
		t = t->parent;
	}
	t->weight--;
	
	if (remove) {
		sliding_remove_node(tree);
		tree->tree->leaves[b] = NULL;
	}
}
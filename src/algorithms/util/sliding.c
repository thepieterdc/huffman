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

huffman_node *sliding_decode_character(adaptive_huffman_tree *tree, byte_queue *window, bit_input_stream *in, FILE *out) {
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

void sliding_update_tree(adaptive_huffman_tree *tree, byte b) {
	huffman_node *t = tree->tree->leaves[b];
	huffman_node *swap_node;
	
	/* Remove the node from the tree. */
	bool remove = t->weight == 1;
	
	fprintf(stderr, "Decreasing %c\n", b);
	huffmantree_print(tree->tree);
	
	while (t->parent) {
		swap_node = tree->nodes[sliding_find_swap(tree, t->weight)];
		if (t != swap_node && swap_node->parent != t && t->parent != swap_node) {
			/* Swap the nodes in the tree. */
			fprintf(stderr, "Swapping: %d - %d\n", t->order_no, swap_node->order_no);
			adaptive_do_swap(tree, t, swap_node);
		}
		t->weight--;
		t = t->parent;
		huffmantree_print(tree->tree);
	}
	t->weight--;
	
	if (remove) {
		fprintf(stderr, "\nRemoving %c\n", b);
		huffman_node *parent = tree->nyt->parent;
		huffman_node *remove_node = parent->right;
		
		huffmantree_print(tree->tree);
		
		tree->nyt->parent = parent->parent;
		if (parent->parent->left == parent) {
			parent->parent->left = tree->nyt;
		} else {
			parent->parent->right = tree->nyt;
		}
		
		parent->left = NULL;
		parent->right = NULL;
		
		huffmannode_free(parent);
		huffmannode_free(remove_node);
		
		tree->amt_nodes -= 2;
		huffmantree_print(tree->tree);
	}
	
	fprintf(stderr, "\n\n\n\n");
}
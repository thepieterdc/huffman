/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <stdlib.h>
#include "adaptive.h"
#include "../../util/binary.h"
#include "../../util/logging.h"
#include "../../util/errors.h"

huffman_node *adaptive_add_character(adaptive_huffman_tree *tree, byte data) {
	if (tree->tree->leaves[data]) error(ERROR_INVALID_INPUT);
	
	huffman_node *parent = tree->nyt->parent;
	huffman_node *newleaf = huffmannode_create_leaf(data, 1);
	newleaf->order_no = (uint_least16_t) (tree->amt_nodes + 1);
	tree->tree->leaves[data] = newleaf;
	
	huffman_node *ret = huffmannode_create_node(tree->nyt, newleaf);
	ret->order_no = tree->amt_nodes;
	ret->parent = parent;
	
	if (parent) {
		parent->left = ret;
	} else {
		tree->tree->root = ret;
	}
	
	tree->nodes[ret->order_no] = ret;
	tree->nodes[newleaf->order_no] = newleaf;
	
	tree->amt_nodes += 2;
	
	return ret;
}

huffman_node *adaptive_decode_character(adaptive_huffman_tree *tree, bit_input_stream *in, FILE *out) {
	huffman_node *cursor = tree->tree->root;
	
	while (cursor->type != NYT && cursor->type != LEAF) {
		bit rd = bis_read_bit(in);
		cursor = rd ? cursor->right : cursor->left;
	}
	
	if (cursor->type == NYT) {
		/* z is a new character; add it to the tree. */
		byte z = bis_read_byte(in);
		huffman_node *o = adaptive_add_character(tree, z);
		putc_unlocked(z, out);
		return o->parent;
	} else {
		putc_unlocked(cursor->data, out);
		return cursor;
	}
}

void adaptive_do_swap(adaptive_huffman_tree *tree, huffman_node *node1, huffman_node *node2) {
	tree->nodes[node1->order_no] = node2;
	tree->nodes[node2->order_no] = node1;
	
	bool node1_left_of_parent = node1->parent->left == node1;
	bool node2_left_of_parent = node2->parent->left == node2;
	
	uint_least16_t temp_o = node1->order_no;
	node1->order_no = node2->order_no;
	node2->order_no = temp_o;
	
	huffman_node *temp = node1->parent;
	node1->parent = node2->parent;
	node2->parent = temp;
	
	if (node1_left_of_parent) {
		node2->parent->left = node2;
	} else {
		node2->parent->right = node2;
	}
	
	if (node2_left_of_parent) {
		node1->parent->left = node1;
	} else {
		node1->parent->right = node1;
	}
}

huffman_node *adaptive_encode_character(adaptive_huffman_tree *tree, byte character, bit_output_stream *out) {
	huffman_node *ret = tree->tree->leaves[character];
	
	if (tree->amt_nodes == 0) {
		bos_feed_byte(out, character);
		ret = NULL;
	} else {
		if (!ret) {
			adaptive_print_code(tree->nyt, out);
			bos_feed_byte(out, character);
		} else {
			adaptive_print_code(ret, out);
		}
	}
	
	if (!ret) {
		/* z is a new character; add it to the tree. */
		huffman_node *o = adaptive_add_character(tree, character);
		ret = o->parent;
	}
	
	return ret;
}

uint_fast16_t adaptive_find_swap(adaptive_huffman_tree *tree, huffman_node *node) {
	register uint_least64_t weight = node->weight;
	for (uint_fast16_t i = node->order_no; i > 0; --i) {
		if (tree->nodes[i - 1]->weight != weight) {
			return i;
		}
	}
	return 0;
}

void adaptive_print_code(huffman_node *node, bit_output_stream *out) {
	uint_fast64_t code = 0;
	size_t codelength = 0;

	huffman_node *cursor = node;
	while (cursor->parent != NULL) {
//		code <<= 1;
//		code |= cursor->parent != cursor;
		checken of byis_feed_byte msb of lsb based is
		waarschijnlijk ook herschrijven naar fwrite64bit
		code opbouwen door & 1 te doen als rechts
		code[codelength++] = cursor->parent->left != cursor;
		cursor = cursor->parent;
	}
	hier nu gewoon byis_feed_byte callen met code en codelength -> niet meer reversen
	for (size_t i = codelength; i > 0; --i) {
		bos_feed_bit(out, code[i - 1]);
	}
}

void adaptive_update_tree(adaptive_huffman_tree *tree, huffman_node *t) {
	huffman_node *swap_node;
	while (t) {
		swap_node = tree->nodes[adaptive_find_swap(tree, t)];
		if (t != swap_node && swap_node->parent != t && t->parent != swap_node) {
			/* Swap the nodes in the tree. */
			adaptive_do_swap(tree, t, swap_node);
		}
		t->weight++;
		t = t->parent;
	}
}
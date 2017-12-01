/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdlib.h>
#include "standard.h"
#include "../../datastructures/min_heap.h"
#include "common.h"
#include "../../util/numerical.h"
#include "../../util/memory.h"
#include "../../util/logging.h"
#include "../../util/errors.h"

/**
 * Recursive step to set the characters in a Huffman tree.
 *
 * @param tree the Huffman tree
 * @param root the root of the current subtree
 * @param in the input stream
 */
static void standard_assign_characters_rec(huffman_tree *tree, huffman_node *root, bit_input_stream *in) {
	if (root->type == LEAF) {
		root->data = bis_read_byte(in);
		tree->leaves[root->data] = root;
	} else {
		standard_assign_characters_rec(tree, root->left, in);
		standard_assign_characters_rec(tree, root->right, in);
	}
}

void standard_assign_characters(huffman_tree *tree, bit_input_stream *in) {
	standard_assign_characters_rec(tree, tree->root, in);
}

/**
 * @internal
 * @param root the root of the tree
 * @param input the input stream
 * @param assign_codes true to assign a code to every node
 * @param depth the current depth of the node
 * @return the maximum tree depth (includes root)
 */
static inline uint_fast8_t
standard_build_tree_from_bits_helper(huffman_node *root, bit_input_stream *input, bool assign_codes, size_t depth) {
	bit rd = bis_read_bit(input);
	root->type = rd ? LEAF : NODE;
	if (!rd) {
		if (depth > 260) error(ERROR_MAXIMUM_HUFFMAN_DEPTH);
		
		root->left = huffmannode_create_node(NULL, NULL);
		root->left->parent = root;
		root->left->code = assign_codes ? huffmancode_create_left(root->code) : NULL;
		uint_fast8_t p1 = standard_build_tree_from_bits_helper(root->left, input, assign_codes, depth + 1);
		
		root->right = huffmannode_create_node(NULL, NULL);
		root->right->parent = root;
		root->right->code = assign_codes ? huffmancode_create_right(root->code) : NULL;
		uint_fast8_t p2 = standard_build_tree_from_bits_helper(root->right, input, assign_codes, depth + 1);
		
		return (uint_fast8_t) (1 + max(p1, p2));
	}
	return 1;
}

uint_fast8_t standard_build_tree_from_bits(huffman_node *root, bit_input_stream *input, bool assign_codes) {
	return standard_build_tree_from_bits_helper(root, input, assign_codes, 0);
}

huffman_tree *standard_build_tree_from_frequencies(const uint_least64_t frequencies[]) {
	huffman_tree *tree = huffmantree_create_empty();
	
	/* Add all bytes to a heap. */
	min_heap *heap = minheap_create(HUFFMAN_MAX_LEAVES);
	for (size_t i = 0; i < HUFFMAN_MAX_LEAVES; ++i) {
		register uint_least64_t freq = frequencies[i];
		if (freq > 0) {
			huffman_node *leaf = huffmannode_create_leaf((byte) i, freq);
			minheap_insert(heap, freq, leaf);
			tree->leaves[i] = leaf;
		}
	}
	
	/* Failsafe for strings containing 1 character. */
	if (heap->size == 1) {
		huffman_node *nullnode = huffmannode_create_leaf(0, 1);
		minheap_insert(heap, nullnode->weight, nullnode);
	}
	
	/* Fill the Huffman tree. */
	while (heap->size > 1) {
		huffman_node *left = minheap_extract_min(heap);
		huffman_node *right = minheap_extract_min(heap);
		huffman_node *parent = huffmannode_create_node(left, right);
		minheap_insert(heap, parent->weight, parent);
	}
	
	tree->root = minheap_find_min(heap);
	
	minheap_free(heap);
	
	return tree;
}

bool standard_data_is_random(huffman_tree *tree) {
	for (size_t i = 0; i < HUFFMAN_MAX_LEAVES; ++i) {
		if (tree->leaves[i] == NULL || tree->leaves[i]->code->length != BITS_IN_BYTE) {
			return false;
		}
	}
	return true;
}

void standard_decode_random(byte_input_stream *in, FILE *out, huffman_tree *tree) {
	/* Create a dictionary for fast lookups. */
	uint_fast8_t dictionary[HUFFMAN_MAX_LEAVES] = {0};
	for (size_t i = 0; i < HUFFMAN_MAX_LEAVES; ++i) {
		uint_fast8_t code = (uint_fast8_t) tree->leaves[i]->code->code;
		dictionary[code] = (uint_fast8_t) i;
	}
	
	/* Decode the input stream using the dictionary. */
	register byte rd = byis_read(in);
	while (in->cursor <= in->buffer_size - 2) {
		putc_unlocked(dictionary[rd], out);
		while (in->cursor < in->buffer_size - 2) {
			rd = byis_read_unsafe(in);
			putc_unlocked(dictionary[rd], out);
		}
		rd = byis_read(in);
	}
	
	/* Decode the remaining byte. */
	register uint_fast8_t indicator = byis_read(in);
	if (indicator != 0) {
		putc_unlocked(dictionary[rd], out);
	}
}

/**
 * Decodes up to the next character in the input stream.
 *
 * @param cursor the start cursor
 * @param in the input stream
 * @return the decoded character
 */
static inline byte standard_decode_character(huffman_node *cursor, bit_input_stream *in) {
	while (cursor->type != LEAF) {
		bit dir = bis_read_bit(in);
		cursor = huffmantree_traverse(cursor, dir);
	}
	return cursor->data;
}

void standard_decode_regular(bit_input_stream *in, FILE *out, huffman_tree *tree, uint_fast8_t maxpath) {
	/* Create max. 8 lookup tables. */
	huffman_node **lookup_tables[min(BITS_IN_BYTE, maxpath)];
	for (size_t i = 0; i < min(BITS_IN_BYTE, maxpath); ++i) {
		uint_least16_t amount_nodes = (uint_least16_t) (2 << i);
		huffman_node **table = mallocate(amount_nodes * sizeof(huffman_node *));
		
		/* Create an entry for every possible code of length i+1. */
		for (size_t j = 0; j < amount_nodes; ++j) {
			huffman_node *cursor = tree->root;
			size_t length = 0;
			while (cursor->type != LEAF && length < i + 1) {
				bit direction = nth_bit_in_byte_msb(j, 7 - i + length);
				cursor = huffmantree_traverse(cursor, direction);
				length++;
			}
			table[j] = cursor;
		}
		
		lookup_tables[i] = table;
	}
	
	while (in->stream->cursor <= in->stream->buffer_size - 2) {
		size_t read_amount = min(bis_bits_left(in), maxpath);
		huffman_node *cursor = tree->root;
		if (read_amount != 0) {
			huffman_node **table = lookup_tables[read_amount - 1];
			size_t tbl = (size_t) bis_get_n_bits(in, read_amount);
			cursor = table[tbl];
			in->current_cursor += read_amount;
			if (cursor->type == LEAF) {
				putc_unlocked(cursor->data, out);
				bis_rewind(in, read_amount - cursor->code->length);
				continue;
			}
		}
		putc_unlocked(standard_decode_character(cursor, in), out);
	}
	
	/* Decode the remaining byte. */
	size_t indicator = huffman_finalize_input(in);
	while (in->current_cursor < indicator) {
		putc_unlocked(standard_decode_character(tree->root, in), out);
	}
	
	/* Free memory allocated by the lookup tables. */
	for (size_t i = 0; i < min(BITS_IN_BYTE, maxpath); ++i) {
		free(lookup_tables[i]);
	}
}

void standard_encode_random(byte_input_stream *in, FILE *out, uint_fast64_t codes[]) {
	register byte b = byis_read_unsafe(in);
	while (in->cursor <= in->buffer_size) {
		putc_unlocked((uint_fast8_t) codes[b], out);
		b = byis_read_unsafe(in);
	}
}

void standard_encode_regular(byte_input_stream *in, bit_output_stream *out, uint_fast64_t codes[],
                             uint_fast8_t code_lengths[]) {
	register byte b = byis_read_unsafe(in);
	while (in->cursor <= in->buffer_size) {
		bos_feed_bits(out, codes[b], code_lengths[b]);
		b = byis_read_unsafe(in);
	}
}

void standard_print_characters(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		putc_unlocked(root->data, out->channel);
	} else {
		standard_print_characters(root->left, out);
		standard_print_characters(root->right, out);
	}
}

void standard_print_tree(huffman_node *root, bit_output_stream *out) {
	if (root->type == LEAF) {
		bos_feed_bit(out, 1);
	} else {
		bos_feed_bit(out, 0);
		
		standard_print_tree(root->left, out);
		standard_print_tree(root->right, out);
	}
}
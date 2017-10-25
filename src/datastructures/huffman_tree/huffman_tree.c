/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <stdio.h>
#include "huffman_tree.h"
#include "../../util/memory.h"

huffman_tree *huffmantree_create(huffman_node *root) {
	huffman_tree *ret = (huffman_tree *) callocate(1, sizeof(huffman_tree));
	
	ret->root = root;
	if (!ret->root) {
		ret->root = huffmannode_create_node(NULL, NULL);
	}
	
	return ret;
}

huffman_tree *huffmantree_create_empty() {
	return (huffman_tree *) callocate(1, sizeof(huffman_tree));
}

void huffmantree_free(huffman_tree *tree) {
	if (tree->root) {
		huffmannode_free(tree->root);
	}
	free(tree);
}

/**
 * Recursive step to set the codes in a Huffman tree.
 *
 * @param root the root of the subtree to print
 * @param code the current code
 */
static void huffmantree_set_codes_rec(huffman_node *root, huffman_code *code) {
	root->code = code;
	
	if (root->left && root->right) {
		huffmantree_set_codes_rec(root->left, huffmancode_create_left(code));
		huffmantree_set_codes_rec(root->right, huffmancode_create_right(code));
	}
}

void huffmantree_set_codes(huffman_tree *tree) {
	huffmantree_set_codes_rec(tree->root, huffmancode_create());
}
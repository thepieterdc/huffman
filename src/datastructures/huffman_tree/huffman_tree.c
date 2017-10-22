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
	ret->nyt = huffmannode_create_nyt();
	
	ret->root = root;
	if (ret->root) {
		ret->root->type = ROOT;
	} else {
		ret->root = huffmannode_create_root(NULL, NULL);
	}
	
	return ret;
}

huffman_tree *huffmantree_create_empty() {
	huffman_tree *ret = (huffman_tree *) callocate(1, sizeof(huffman_tree));
	ret->nyt = huffmannode_create_nyt();
	return ret;
}

void huffmantree_free(huffman_tree *tree) {
	if (tree->root) {
		huffmannode_free(tree->root);
	}
	if (tree->nyt) {
		huffmannode_free(tree->nyt);
	}
	free(tree);
}

/**
 * Recursive step to print a Huffman tree to stderr.
 *
 * @param root the root of the subtree to print
 * @param indent the indentation level
 */
static void huffmantree_print_rec(huffman_node *root, uint_least16_t indent) {
	for (size_t i = 0; i < indent; ++i) {
		fprintf(stderr, "\t");
	}
	
	if (root->type == NODE) {
		fprintf(stderr, "NODE[a=%ld, o=%d]\n", root->weight, root->order_no);
	} else if (root->type == LEAF) {
		fprintf(stderr, "LEAF[a=%ld, o=%d, data=%d]\n", root->weight, root->order_no, root->data);
	} else if (root->type == ROOT) {
		fprintf(stderr, "ROOT[a=%ld, o=%d]\n", root->weight, root->order_no);
	} else if (root->type == NYT) {
		fprintf(stderr, "NYT[a=%ld, o=%d]\n", root->weight, root->order_no);
	}
	
	if (root->left && root->right) {
		huffmantree_print_rec(root->left, (uint_least16_t) (indent + 1));
		huffmantree_print_rec(root->right, (uint_least16_t) (indent + 1));
	}
}

void huffmantree_print(huffman_tree *tree) {
	huffmantree_print_rec(tree->root, 0);
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

void huffmantree_set_root(huffman_tree *tree, huffman_node *root) {
	if (tree->root) {
		huffmannode_free(tree->root);
	}
	tree->root = root;
	tree->root->type = ROOT;
}
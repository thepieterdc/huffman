/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "util/arguments.h"
#include "datastructures/huffman_tree.h"
#include "util/logging.h"

huffman_node *find_parent_of_node(huffman_node *tree, huffman_node *node) {
	huffman_node *partialres = NULL;
	if (tree->left != NULL) {
		if (tree->left->data == node->data && tree->left->type == node->type) {
			return tree;
		} else {
			partialres = find_parent_of_node(tree->left, node);
		}
		
		if (partialres != NULL) {
			return partialres;
		}
	}
	
	if (tree->right != NULL) {
		if (tree->right->data == node->data && tree->right->type == node->type) {
			return tree;
		} else {
			partialres = find_parent_of_node(tree->right, node);
		}
		
		if (partialres != NULL) {
			return partialres;
		}
	}
	
	return NULL;
}

int main(int argc, char **argv) {
	FILE *in = fopen("tests/testvectors/aabcdad.txt", "rb");
	
	// nyt = node met data 0; blad met data 0 zou \0 zijn
	huffman_node *nyt = huffman_create_node(NULL, NULL);
	nyt->weight = 0;
	
	int frequencies[256] = {0};
	
	huffman_node *tree = nyt;
	
	int z;
	while ((z = (char) getc(in)) > -1) {
		printf("%c\n", z);
		
		huffman_node *t = NULL;
		
		if (frequencies[z]++ != 0) {
			info("Already in tree.");
		} else {
			huffman_node *parent_node = find_parent_of_node(tree, nyt);
			huffman_node *z_node = huffman_create_leaf((byte) z, 0);
			z_node->weight = 1;
			huffman_node *o_node = huffman_create_node(nyt, z_node);
			
			//insert into original tree//
			if (parent_node != NULL) {
				parent_node->left = o_node;
				t = parent_node;
				info("Added in tree.");
			} else {
				info("No tree yet.");
				//no tree yet//
				tree = o_node;
				continue;
			}
		}
//
//		huffman_node *tbar;
//		while (tree != t) {
////			tbar = find_tbar(tree, t);
////			printf("%d\n", tbar != NULL);
//			break;
//		}
	}
	
	huffman_visualise_tree(tree);

//	//FILE *in = stdin;
//	FILE *out = stdout;
//
//	_huffmanfunction function = argument_parse(argc, argv);
//	function(in, out);
	
	return 0;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "util/arguments.h"
#include "datastructures/huffman_tree.h"
#include "util/logging.h"

void increment_all_ordernumbers(huffman_node *tree) {
	tree->order_no += 2;
	if (tree->left != NULL) {
		increment_all_ordernumbers(tree->left);
	}
	if (tree->right != NULL) {
		increment_all_ordernumbers(tree->right);
	}
}

huffman_node *find_tbar(huffman_node *tree, huffman_node *t) {
	huffman_node *current_best = NULL;
	if (tree->weight == t->weight) {
		current_best = tree;
	}
	
	if (tree->left != NULL) {
		huffman_node *left_best = find_tbar(tree->left, t);
		if (left_best != NULL) {
			if (current_best == NULL || current_best->order_no < left_best->order_no) {
				current_best = left_best;
			}
		}
	}
	
	if (tree->right != NULL) {
		huffman_node *right_best = find_tbar(tree->right, t);
		if (right_best != NULL) {
			if (current_best == NULL || current_best->order_no < right_best->order_no) {
				current_best = right_best;
			}
		}
	}
	return current_best;
}

huffman_node *find_parent_of_node(huffman_node *tree, huffman_node *node) {
	huffman_node *partialres = NULL;
	if (tree->left != NULL) {
		if (tree->left == node) {
			return tree;
		}
		partialres = find_parent_of_node(tree->left, node);
	}
	
	if (tree->right != NULL) {
		if (tree->right == node) {
			return tree;
		}
		
		if (partialres == NULL) {
			partialres = find_parent_of_node(tree->right, node);
		}
	}
	
	return partialres;
}

int main(int argc, char **argv) {
	FILE *in = fopen("tests/testvectors/graag.txt", "rb");
	
	// nyt = node met data 0; blad met data 0 zou \0 zijn
	huffman_node *nyt = huffman_create_node(NULL, NULL);
	nyt->weight = 500000;
	
	huffman_node *nodes[256] = {};
	
	huffman_node *tree = nyt;
	
	int z;
	while ((z = (char) getc(in)) > -1) {
		char cbuf[20] = "Character ";
		cbuf[10] = (char) z;
		cbuf[11] = '\0';
		info(cbuf);
		
		huffman_node *t = NULL;
		
		if (nodes[z] != NULL) {
			info("Already in tree.\n");
			t = nodes[z];
		} else {
			huffman_node *parent_node = find_parent_of_node(tree, nyt);
			huffman_node *z_node = huffman_create_leaf((byte) z, 0);
			nodes[z] = z_node;
			z_node->weight = 1;
			z_node->order_no = 1;
			huffman_node *o_node = huffman_create_node(nyt, z_node);
			o_node->weight = 1;
			
			//insert into original tree//
			if (parent_node != NULL) {
				fprintf(stderr, "Nyt ding: %d\n", nyt->order_no);
				fprintf(stderr, "Parent: %d\n", parent_node->order_no);
				increment_all_ordernumbers(tree);
				nyt->order_no = 0;
				o_node->order_no = 2;
				
				fprintf(stderr, "Left node van parent: %d\n", parent_node->left->weight);
				
				parent_node->left = o_node;
				t = parent_node;
				info("Added in tree.\n");
			} else {
				info("No tree yet.\n");
				//no tree yet//
				nyt->order_no = 0;
				o_node->order_no = 2;
				tree = o_node;
				
				
				huffman_visualise_tree(tree);
				continue;
			}
		}
		
		info("Pre-loop");
		huffman_visualise_tree(tree);
		
		huffman_node *tbar;
		//zolang t niet de wortel is//
		while (tree != t && t != NULL) {
			info("Loop");
			tbar = find_tbar(tree, t);
			//t' is niet de ouder van t
			if (tbar->left != t && tbar->right != t) {
				//swap t en t'//
				huffman_node t_node = *t;
				*t = *tbar;
				*tbar = t_node;
				
				nodes[t->data] = t;
				nodes[tbar->data] = tbar;
				
				//swap ordernummers van t en t'
				uint_fast64_t order_t = t->order_no;
				uint_fast64_t order_tbar = tbar->order_no;
				t->order_no = order_tbar;
				tbar->order_no = order_t;
			}
			t->weight++;
			t = find_parent_of_node(tree, t);
			
			huffman_visualise_tree(tree);
		}
		
		info("Loop done");
		t->weight++;
		
		huffman_visualise_tree(tree);
		
	}
	
	huffman_visualise_tree(tree);


//	//FILE *in = stdin;
//	FILE *out = stdout;
//
//	_huffmanfunction function = argument_parse(argc, argv);
//	function(in, out);
	
	return 0;
}
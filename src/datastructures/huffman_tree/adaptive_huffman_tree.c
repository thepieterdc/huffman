/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <stdlib.h>
#include "adaptive_huffman_tree.h"
#include "../../util/memory.h"

adaptive_huffman_tree *adaptivehuffmantree_create() {
	adaptive_huffman_tree *ret = (adaptive_huffman_tree *) callocate(1, sizeof(adaptive_huffman_tree));
	ret->nyt = huffmannode_create_nyt();
	ret->nyt->order_no = HUFFMAN_MAX_NODES - 1;
	ret->tree = huffmantree_create(ret->nyt);
	ret->nodes[HUFFMAN_MAX_NODES - 1] = ret->tree->root;
	return ret;
}

void adaptivehuffmantree_free(adaptive_huffman_tree *aht) {
	huffmantree_free(aht->tree);
	free(aht);
}

void adaptivehuffmantree_initialise(adaptive_huffman_tree *aht, huffman_tree *tree) {
	aht->tree = tree;
	aht->nyt = huffmannode_create_nyt();
	aht->nyt->order_no = HUFFMAN_MAX_NODES - 1;
	//set ordernumbers (BFS!!!!)
	//add ordernumbers @  aht->nodes
	//set aht->amt_nodes
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include "adaptive_huffman_tree.h"
#include "../../util/memory.h"

adaptive_huffman_tree *adaptivehuffmantree_create() {
	adaptive_huffman_tree *ret = (adaptive_huffman_tree *) callocate(1, sizeof(adaptive_huffman_tree));
	ret->nyt = huffmannode_create_nyt();
	ret->tree = huffmantree_create(ret->nyt);
	ret->nodes[0] = ret->tree->root;
	return ret;
}

void adaptivehuffmantree_free(adaptive_huffman_tree *aht) {
	huffmantree_free(aht->tree);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datastructure_huffmannode.h"
#include "test_unit.h"
#include "../src/datastructures/huffman_tree/huffman_node.h"

char *test_huffmannode_create_free() {
	huffman_node *leaf = huffmannode_create_leaf(5, 1);
	assertThat(leaf != NULL);
	assertThat(leaf->type == LEAF);
	
	huffman_node *nyt = huffmannode_create_nyt();
	assertThat(nyt != NULL);
	assertThat(nyt->type == NYT);
	
	huffman_node *node = huffmannode_create_node(leaf, nyt);
	assertThat(node != NULL);
	assertThat(node->type == NODE);
	
	huffmannode_free(node);
	
	return 0;
}
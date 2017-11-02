/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datastructure_huffmannode.h"
#include "test_unit.h"
#include "../src/datastructures/huffman_tree/huffman_node.h"

const char *test_huffmannode_create_free() {
	huffman_node *leaf = huffmannode_create_leaf(5, 1);
	assertNotNull(leaf);
	assertEquals(leaf->type, LEAF);
	
	huffman_node *nyt = huffmannode_create_nyt();
	assertNotNull(nyt);
	assertEquals(nyt->type, NYT);
	
	huffman_node *node = huffmannode_create_node(leaf, nyt);
	assertNotNull(node);
	assertEquals(node->type, NODE);
	
	huffmannode_free(node);
	
	return 0;
}
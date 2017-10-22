/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datastructure_huffmannode.h"
#include "test_unit.h"
#include "../src/datastructures/huffman_tree/huffman_node.h"

char *test_huffmannode_create_free_reset_counter() {
	huffman_reset_ordercounter();
	
	huffman_node *leaf = huffmannode_create_leaf(5, 1);
	assertThat(leaf != NULL);
	assertThat(leaf->order_no == 0);
	
	huffman_node *node = huffmannode_create_node(NULL, NULL);
	assertThat(node != NULL);
	assertThat(node->order_no == 1);
	
	huffman_reset_ordercounter();
	
	huffman_node *node2 = huffmannode_create_node(NULL, NULL);
	assertThat(node2 != NULL);
	assertThat(node2->order_no == 0);
	
	huffmannode_free(leaf);
	huffmannode_free(node);
	huffmannode_free(node2);
	
	return 0;
}
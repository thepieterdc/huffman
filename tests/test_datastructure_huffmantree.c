/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_datastructure_huffmantree.h"
#include "test_unit.h"
#include "../src/datastructures/huffman_tree.h"

char *test_huffmantree_create_free_reset_counter() {
	huffman_reset_ordercounter();
	
	huffman_node *leaf = huffman_create_leaf(5, 1);
	assertThat(leaf != NULL);
	assertThat(leaf->order_no == 0);
	
	huffman_node *node = huffman_create_node(NULL, NULL);
	assertThat(node != NULL);
	assertThat(node->order_no == 1);
	
	huffman_reset_ordercounter();
	
	huffman_node *node2 = huffman_create_node(NULL, NULL);
	assertThat(node2 != NULL);
	assertThat(node2->order_no == 0);
	
	huffman_free(leaf);
	huffman_free(node);
	huffman_free(node2);
	
	return 0;
}
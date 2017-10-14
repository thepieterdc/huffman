/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H

#include <unistd.h>
#include "../datatypes/bit.h"

/**
 * Different types of nodes.
 */
enum huffman_node_type {NODE, LEAF};

/**
 * A node in the Huffman tree.
 */
typedef struct huffman_node {
	enum huffman_node_type type;
	byte data;
	uint8_t order_no;
	uint8_t weight;
	struct huffman_node *left;
	struct huffman_node *right;
} huffman_node;

/**
 * Creates a new Huffman leaf-node.
 *
 * @return the created node
 */
huffman_node *huffman_create_leaf(byte data, uint8_t weight);

/**
 * Creates a new Huffman node-node.
 *
 * @return the created node
 */
huffman_node *huffman_create_node();

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H */
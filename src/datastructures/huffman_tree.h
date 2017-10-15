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
enum huffman_node_type {
	NODE, LEAF
};

/**
 * A node in the Huffman tree.
 */
typedef struct huffman_node {
	enum huffman_node_type type;
	byte data;
	uint8_t order_no;
	size_t weight;
	struct huffman_node *left;
	struct huffman_node *right;
} huffman_node;

/**
 * Creates a new Huffman leaf-node.
 *
 * @param data the value of this leaf
 * @param weight the weight of this leaf
 * @return the created node
 */
huffman_node *huffman_create_leaf(byte data, size_t weight);

/**
 * Creates a new Huffman node-node.
 *
 * @param left the left child
 * @param right the right child
 * @return the created node
 */
huffman_node *huffman_create_node(huffman_node *left, huffman_node *right);

/**
 * Frees a Huffman leaf/node including its children, recursively.
 *
 * @param node the node to free
 */
void huffman_free(huffman_node *node);

/**
 * Resets the order-no counter.
 */
void huffman_reset_ordercounter();

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H */
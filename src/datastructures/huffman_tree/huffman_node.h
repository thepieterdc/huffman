/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANNODE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANNODE_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdint.h>
#include "../../datatypes/huffman_code.h"

/**
 * Different types of nodes.
 */
enum huffman_node_type {
	NODE, LEAF, NYT
};

/**
 * A node in the Huffman tree.
 */
typedef struct huffman_node {
	enum huffman_node_type type;
	byte data;
	uint_least16_t order_no;
	uint_least64_t weight;
	huffman_code *code;
	struct huffman_node *parent;
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
huffman_node *huffmannode_create_leaf(byte data, uint_least64_t weight);

/**
 * Creates a new Huffman node-node.
 *
 * @param left the left child
 * @param right the right child
 * @return the created node
 */
huffman_node *huffmannode_create_node(huffman_node *left, huffman_node *right);

/**
 * Creates a new Huffman NYT-node.
 *
 * @return the created node
 */
huffman_node *huffmannode_create_nyt();

/**
 * Frees a Huffman leaf/node including its children, recursively.
 *
 * @param node the node to free
 */
void huffmannode_free(huffman_node *node);

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANNODE_H */
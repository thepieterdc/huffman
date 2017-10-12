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
	int data;
	size_t weight;
	struct huffman_node *left;
	struct huffman_node *right;
} huffman_node;

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H */
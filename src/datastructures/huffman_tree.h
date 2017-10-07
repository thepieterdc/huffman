/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_HUFFMAN_TREE_H
#define HUFFMAN_UTIL_HUFFMAN_TREE_H

#include <unistd.h>

/**
 * Different types of nodes.
 */
enum node_type {NODE, LEAF};

/**
 * A node in the Huffman tree.
 */
typedef struct huffman_node {
	enum node_type type;
	int value;
	size_t weight;
	struct huffman_node *left;
	struct huffman_node *right;
} huffman_node;

#endif /* HUFFMAN_UTIL_HUFFMAN_TREE_H */

/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANTREE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANTREE_H

#include "huffman_node.h"

#define HUFFMAN_MAX_LEAVES 256

/**
 * A Huffman tree.
 */
typedef struct huffman_tree {
	struct huffman_node *leaves[HUFFMAN_MAX_LEAVES];
	struct huffman_node *root;
} huffman_tree;



#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_HUFFMANTREE_H */
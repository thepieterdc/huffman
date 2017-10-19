/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H
#define HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H

#include <unistd.h>
#include "../datatypes/bit.h"
#include "../datatypes/huffman_code.h"
#include "../io/output/bit_output_stream.h"
#include "../io/input/bit_input_stream.h"

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
	huffman_code *code;
	byte data;
	uint_fast64_t order_no;
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
 * Prints a Huffman tree to the supplied output stream.
 *
 * @param root the root of the tree to print
 * @param out the output stream to write to
 */
void huffman_print_tree(huffman_node *root, bit_output_stream *out);

/**
 * Prints a Huffman tree to stderr.
 *
 * @param root the root of the tree
 */
void huffman_visualise_tree(huffman_node *root);

/**
 * Resets the order-no counter.
 */
void huffman_reset_ordercounter();

#endif /* HUFFMAN_DATASTRUCTURES_HUFFMANTREE_H */
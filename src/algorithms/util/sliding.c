/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "sliding.h"
#include "../../util/logging.h"

void sliding_decrease_character(adaptive_huffman_tree *tree, byte b) {
	fprintf(stderr, "Decreasing %c\n", b);
	huffmantree_print(tree->tree);
	huffman_node *node = tree->tree->leaves[b];
}
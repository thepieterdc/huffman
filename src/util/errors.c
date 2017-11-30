/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "errors.h"

const char *_error_messages[7] = {"Failed to allocate memory.",
                            "Requested index is out of bounds.",
                            "The heap contains no more elements.",
                            "Reached end of input while reading.",
                            "The queue contains no more elements.",
							"Invalid input detected.",
							"Maximum Huffman tree depth exceeded. Tree is invalid."};
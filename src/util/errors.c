/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "errors.h"

char *_error_messages[6] = {"Failed allocating memory.",
                            "Requested index is out of bounds.",
                            "The heap contains no more elements.",
                            "Syntax: ./huffman -t [1..5] [-c|-d]",
                            "Reached end of input while reading.",
							"Input is empty."};

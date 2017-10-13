/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "errors.h"

char *_error_messages[6] = {"Failed allocating memory.",
                            "Requested index is out of bounds.",
                            "There are no more elements in the heap.",
                            "Invalid algorithm parameter.",
                            "Invalid mode parameter.",
							"Syntax: ./huffman -t [1..5] [-c|-d]"};

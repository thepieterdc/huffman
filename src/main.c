#include "util/arguments.h"

/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

int main(int argc, char **argv) {
	FILE *in = stdin;
	FILE *out = stdout;
	
	_huffmanfunction function(in, out);
	return 0;
}
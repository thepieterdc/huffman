/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "util/arguments.h"

int main(int argc, char **argv) {
	//FILE *in = fopen("tests/testvectors/graag.txt", "rb");
	
	FILE *in = stdin;
	FILE *out = stdout;
	
	_huffmanfunction function = argument_parse(argc, argv);
	function(in, out);
	
	return 0;
}
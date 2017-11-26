/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <time.h>
#include "util/arguments.h"

int main(int argc, char **argv) {
//	FILE *in = stdin;
	FILE *in = fopen("tests/testvectors/banaan.out", "rb");
	FILE *out = stdout;
	
	_huffmanfunction function = argument_parse(argc, argv);

#ifdef IS_DEBUG
	clock_t tic = clock();
#endif
	
	function(in, out);

#ifdef IS_DEBUG
	clock_t toc = clock();
	fprintf(stderr, "Time elapsed: %f seconds\n", (double) (toc - tic) / CLOCKS_PER_SEC);
#endif
	
	return 0;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <time.h>
#include "util/arguments.h"

int main(int argc, char **argv) {
	/* Input and output streams. */
	FILE *in = stdin;
	FILE *out = stdout;
	
	/* Determine the required encode/decode function. */
	_huffmanfunction function = argument_parse(argc, argv);

#ifdef IS_DEBUG
	clock_t tic = clock();
#endif

	/* Execute the Huffman function. */
	function(in, out);

#ifdef IS_DEBUG
	clock_t toc = clock();
	fprintf(stderr, "Time elapsed: %f seconds\n", (double) (toc - tic) / CLOCKS_PER_SEC);
#endif
	
	return 0;
}
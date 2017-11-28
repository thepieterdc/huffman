/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <time.h>
#include "util/arguments.h"
#include "io/output/bit_output_stream.h"

int main(int argc, char **argv) {
	FILE *in = stdin;
	FILE *out = stdout;
	
	bit_output_stream *bos = bos_create(out);
	bos_feed_bits(bos, 0xFF, 8);
	bos_feed_bits(bos, 0, 8);
	bos_feed_bits(bos, 0xFF, 8);
	bos_feed_bits(bos, 0, 8);
	bos_feed_bits(bos, 0xFF, 8);
	bos_feed_bits(bos, 0, 8);
	bos_feed_bits(bos, 0xFF, 8);
	bos_feed_bits(bos, 0x21, 9);
	bos_feed_bit(bos, 1);
	bos_feed_bit(bos, 1);
	
	bos_flush(bos);
	bos_free(bos);
	
//	_huffmanfunction function = argument_parse(argc, argv);

#ifdef IS_DEBUG
	clock_t tic = clock();
#endif

//	function(in, out);

#ifdef IS_DEBUG
	clock_t toc = clock();
	fprintf(stderr, "Time elapsed: %f seconds\n", (double) (toc - tic) / CLOCKS_PER_SEC);
#endif
	
	return 0;
}
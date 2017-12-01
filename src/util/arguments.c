/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "arguments.h"
#include "../algorithms/standard.h"
#include "../algorithms/adaptive.h"
#include "../algorithms/sliding.h"
#include "../algorithms/twopass.h"
#include "../algorithms/blockwise.h"

_huffmanfunction compressionfunctions[5] = {(_huffmanfunction) huffman_standard_compress,
                                            (_huffmanfunction) huffman_adaptive_compress,
                                            (_huffmanfunction) huffman_sliding_compress,
                                            (_huffmanfunction) huffman_twopass_compress,
                                            (_huffmanfunction) huffman_blockwise_compress};

_huffmanfunction decompressionfunctions[5] = {(_huffmanfunction) huffman_standard_decompress,
                                              (_huffmanfunction) huffman_adaptive_decompress,
                                              (_huffmanfunction) huffman_sliding_decompress,
                                              (_huffmanfunction) huffman_twopass_decompress,
                                              (_huffmanfunction) huffman_blockwise_decompress};

const enum algorithm algorithm_from_opt(const char opt) {
	int optval = char_to_int(opt);
	if (optval < 1 || optval > 5) {
		usage_display(stderr);
		exit(64);
	}
	return (enum algorithm) (optval - 1);
}

const _huffmanfunction argument_parse(const int argc, char **argv) {
	enum algorithm algorithm = STANDARD;
	bool algorithm_set = false;
	
	enum mode mode = COMPRESS;
	bool mode_set = false;
	
	int opt;
	while ((opt = getopt(argc, argv, "t:cd")) != -1) {
		switch (opt) {
			case 'c':
				mode = COMPRESS;
				mode_set = true;
				break;
			
			case 'd':
				mode = DECOMPRESS;
				mode_set = true;
				break;
			
			case 't':
				algorithm = algorithm_from_opt(optarg[0]);
				algorithm_set = true;
				break;
			
			default:
				usage_display(stderr);
				exit(64);
		}
	}
	
	if (!algorithm_set || !mode_set) {
		usage_display(stderr);
		exit(64);
	}
	
	if (mode == COMPRESS) {
		return compressionfunctions[algorithm];
	}
	
	return decompressionfunctions[algorithm];
}

void usage_display(FILE *channel) {
	fprintf(channel,
	        "Usage: huffman [-cd] [-t algorithm]\n"
			        "Reads from standard input and sends either encoded or decoded bytes to standard output.\n"
			        "\n"
			        "  -c\t\t\t\t encode the input\n"
			        "  -d\t\t\t\t decode the input\n"
			        "  -t algorithm\t\t specify which encoding/decoding algorithm to use\n"
			        "\t\t\t\t\t 1 - Standard Huffman\n"
			        "\t\t\t\t\t 2 - Adaptive Huffman\n"
			        "\t\t\t\t\t 3 - Adaptive Huffman (sliding window)\n"
			        "\t\t\t\t\t 4 - Two-pass Adaptive Huffman\n"
			        "\t\t\t\t\t 5 - Blockwise Adaptive Huffman\n"
			        "\n"
			        "Created by Pieter De Clercq. All rights reserved.\n"
	);
}

const enum mode mode_from_opt(const char opt) {
	if (opt != 'c' && opt != 'd') {
		usage_display(stderr);
		exit(64);
	}
	
	if (opt == 'c') {
		return COMPRESS;
	}
	return DECOMPRESS;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <unistd.h>
#include "arguments.h"
#include "../algorithms/standard.h"
#include "logging.h"
#include "errors.h"

_huffmanfunction compressionfunctions[1] = {(_huffmanfunction) huffman_standard_compress};

_huffmanfunction decompressionfunctions[1] = {(_huffmanfunction) huffman_standard_decompress};

enum algorithm algorithm_from_opt(char opt) {
	int optval = char_to_int(opt);
	if (optval < 1 || optval > 5) {
		error(ERROR_ARGUMENT_ALGORITHM);
	}
	return (enum algorithm) (optval - 1);
}

_huffmanfunction argument_parse(int argc, char **argv) {
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
				error(ERROR_SYNTAX_INVALID);
				break;
		}
	}
	
	if (!algorithm_set || !mode_set) {
		error(ERROR_SYNTAX_INVALID);
	}
	
	if (mode == COMPRESS) {
		return compressionfunctions[algorithm];
	}
	
	return decompressionfunctions[algorithm];
}

enum mode mode_from_opt(char opt) {
	if (opt != 'c' && opt != 'd') {
		error(ERROR_ARGUMENT_MODE);
	}
	
	if (opt == 'c') {
		return COMPRESS;
	}
	return DECOMPRESS;
}
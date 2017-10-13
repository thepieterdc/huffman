/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "arguments.h"
#include "../algorithms/standard.h"
#include "logging.h"
#include "errors.h"

_huffmanfunction compressionfunctions[1] = {huffman_standard_compress};

_huffmanfunction decompressionfunction[1] = {huffman_standard_decompress};

enum algorithm algorithm_from_opt(char opt) {
	int optval = char_to_int(opt);
	if (optval < 1 || optval > 5) {
		error(ERROR_ARGUMENT_ALGORITHM);
	}
	return (enum algorithm) (optval - 1);
}

_huffmanfunction *argument_parse(int argc, char **argv) {

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
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

_compressionfunction compressionfunctions[1] = {huffman_standard_compress};

_decompressionfunction decompressionfunction[1] = {huffman_standard_decompress};

//
//arguments *argument_parse(int argc, char **argv) {
//	arguments *args = (arguments *) malloc(sizeof(arguments));
//
//	int c;
//	while((c = getopt(argc, argv, "t:cd")) != -1) {
//		switch(c) {
//			case 't':
//				args->algorithm = ;
//				break;
//		}
//		printf("%d\n%s\n", c, optarg);
//	}
//
//	return args;
//}
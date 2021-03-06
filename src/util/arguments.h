/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_ARGUMENTS_H
#define HUFFMAN_UTIL_ARGUMENTS_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include "string.h"

/**
 * A Huffman compression or decompression function.
 *
 * @param input the input data to process
 * @param output the output channel
 */
typedef void (*_huffmanfunction)(FILE *input, FILE *output);

/**
 * Algorithms.
 */
enum algorithm {
	STANDARD, ADAPTIVE, SLIDING, TWO_PASS, BLOCKWISE
};

/**
 * Operation modes.
 */
enum mode {
	COMPRESS, DECOMPRESS
};

/**
 * Compression functions.
 */
extern _huffmanfunction compressionfunctions[];

/**
 * Decompression functions.
 */
extern _huffmanfunction decompressionfunctions[];

/**
 * Gets the correct algorithm for a given option flag.
 *
 * @param opt the option flag given
 * @return the algorithm
 */
const enum algorithm algorithm_from_opt(char opt);

/**
 * Gets the appropriate Huffman function to execute.
 *
 * @param argc the amount of arguments
 * @param argv the arguments
 * @return the required Huffman function
 */
const _huffmanfunction argument_parse(int argc, char **argv);

/**
 * Displays the usage instructions for this application.
 *
 * @param channel the output channel to write the instructions to
 */
void usage_display(FILE *channel);

/**
 * Gets the correct mode for a given option flag.
 *
 * @param opt the option flag given
 * @return the mode
 */
const enum mode mode_from_opt(char opt);

#endif /* HUFFMAN_UTIL_ARGUMENTS_H */
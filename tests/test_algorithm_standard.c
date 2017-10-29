/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_algorithm_standard.h"
#include "test_algorithm.h"
#include "../src/algorithms/standard.h"
#include "test_unit.h"

char *test_algorithm_standard() {
	_huffmanfunction enc = compressionfunctions[STANDARD];
	_huffmanfunction dec = decompressionfunctions[STANDARD];
	assertEquals(test_huffman_algorithm(enc, dec), 0);
	return 0;
}
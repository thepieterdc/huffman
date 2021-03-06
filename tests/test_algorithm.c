/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "test_algorithm.h"
#include "test_unit.h"
#include "../src/util/memory.h"

#define TEST_ALGORITHM_TESTVECTORS "./tests/testvectors/"

/**
 * Tests a Huffman algorithm.
 *
 * @param encoder the encoding function
 * @param decoder the decoding function
 * @return null if test was succesful
 */
static const char *test_huffman_algorithm(const _huffmanfunction encode, const _huffmanfunction decode) {
	DIR *testvectors = opendir(TEST_ALGORITHM_TESTVECTORS);
	assertNotNull(testvectors);
	
	struct dirent *dp;
	while ((dp = readdir(testvectors)) != NULL) {
		string ext = strrchr(dp->d_name, '.');
		if (ext && str_equals(ext, ".in")) {
			char *vector = str_concat(TEST_ALGORITHM_TESTVECTORS, dp->d_name);
			
			FILE *input = fopen(vector, "rb");
			assertNotNull(input);
			
			char *encoded;
			size_t encoded_size;
			
			char *decoded;
			size_t decoded_size;
			
			FILE *input_stream = open_memstream(&encoded, &encoded_size);
			
			encode(input, input_stream);
			
			FILE *encoded_stream = fmemopen(encoded, encoded_size, "rb");
			FILE *output_stream = open_memstream(&decoded, &decoded_size);
			
			decode(encoded_stream, output_stream);
			
			FILE *raw = fopen(vector, "rb");
			assertNotNull(raw);
			
			fseek(raw, 0, SEEK_END);
			size_t raw_size = (size_t) ftell(raw);
			fseek(raw, 0, SEEK_SET);
			
			char *raw_buffer = (char *) mallocate((raw_size + 1) * sizeof(char));
			size_t last = fread(raw_buffer, sizeof(char), raw_size, raw);
			raw_buffer[last] = '\0';
			
			assertEquals(raw_size, decoded_size);
			assertTrue(str_equals(decoded, raw_buffer));
			
			free(raw_buffer);
			fclose(raw);
			
			fclose(output_stream);
			fclose(encoded_stream);
			
			fclose(input_stream);
			
			free(decoded);
			free(encoded);
			
			free(vector);
		}
	}
	
	closedir(testvectors);
	
	return 0;
}

const char *test_algorithm_adaptive() {
	_huffmanfunction enc = compressionfunctions[ADAPTIVE];
	_huffmanfunction dec = decompressionfunctions[ADAPTIVE];
	assertEquals(test_huffman_algorithm(enc, dec), 0);
	return 0;
}

const char *test_algorithm_blockwise() {
	_huffmanfunction enc = compressionfunctions[BLOCKWISE];
	_huffmanfunction dec = decompressionfunctions[BLOCKWISE];
	assertEquals(test_huffman_algorithm(enc, dec), 0);
	return 0;
}

const char *test_algorithm_sliding() {
	_huffmanfunction enc = compressionfunctions[SLIDING];
	_huffmanfunction dec = decompressionfunctions[SLIDING];
	assertEquals(test_huffman_algorithm(enc, dec), 0);
	return 0;
}

const char *test_algorithm_standard() {
	_huffmanfunction enc = compressionfunctions[STANDARD];
	_huffmanfunction dec = decompressionfunctions[STANDARD];
	
	DIR *testvectors = opendir(TEST_ALGORITHM_TESTVECTORS);
	assertNotNull(testvectors);
	
	struct dirent *dp;
	while ((dp = readdir(testvectors)) != NULL) {
		string ext = strrchr(dp->d_name, '.');
		if (ext && str_equals(ext, ".in")) {
			char *vector = str_concat(TEST_ALGORITHM_TESTVECTORS, dp->d_name);
			
			FILE *input = fopen(vector, "rb");
			assertNotNull(input);
			
			char *encoded;
			size_t encoded_size;
			
			char *decoded;
			size_t decoded_size;
			
			FILE *input_stream = open_memstream(&encoded, &encoded_size);
			
			enc(input, input_stream);
			
			FILE *encoded_stream = fmemopen(encoded, encoded_size, "rb");
			FILE *output_stream = open_memstream(&decoded, &decoded_size);
			
			dec(encoded_stream, output_stream);
			
			FILE *raw = fopen(vector, "rb");
			assertNotNull(raw);
			
			fseek(raw, 0, SEEK_END);
			size_t raw_size = (size_t) ftell(raw);
			fseek(raw, 0, SEEK_SET);
			
			char raw_buffer[raw_size + 1];
			size_t last = fread(raw_buffer, sizeof(char), raw_size, raw);
			raw_buffer[last] = '\0';
			
			assertEquals(raw_size, decoded_size);
			assertTrue(str_equals(decoded, raw_buffer));
			
			fclose(raw);
			
			fclose(output_stream);
			fclose(encoded_stream);
			
			fclose(input_stream);
			
			free(decoded);
			free(encoded);
			
			free(vector);
		}
	}
	
	closedir(testvectors);

//	assertEquals(test_huffman_algorithm(enc, dec), 0);
	return 0;
}

const char *test_algorithm_twopass() {
	_huffmanfunction enc = compressionfunctions[TWO_PASS];
	_huffmanfunction dec = decompressionfunctions[TWO_PASS];
	assertEquals(test_huffman_algorithm(enc, dec), 0);
	return 0;
}
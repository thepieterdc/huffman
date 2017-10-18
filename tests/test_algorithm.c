/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "test_algorithm.h"
#include "test_unit.h"
#include "../src/util/logging.h"

#define TEST_ALGORITHM_TESTVECTORS "./tests/testvectors/"

char *test_huffman_algorithm(_huffmanfunction encode, _huffmanfunction decode) {
	DIR *testvectors = opendir(TEST_ALGORITHM_TESTVECTORS);
	assertThat(testvectors != NULL);
	
	struct dirent *dp;
	while ((dp = readdir(testvectors)) != NULL) {
		if (dp->d_type == DT_REG) {
			string ext = strrchr(dp->d_name, '.');
			if (!ext || !str_equals(ext, ".txt")) {
				continue;
			}
		} else {
			continue;
		}
		
		char *vector = str_concat(TEST_ALGORITHM_TESTVECTORS, dp->d_name);
		
		FILE *input = fopen(vector, "rb");
		assertThat(input != NULL);
		
		char *encoded;
		size_t encoded_size;
		
		char *decoded;
		size_t decoded_size;
		
		encode(input, open_memstream(&encoded, &encoded_size));
		
		FILE *encoded_stream = fmemopen(encoded, encoded_size, "rb");
		
		decode(encoded_stream, open_memstream(&decoded, &decoded_size));
		
		fclose(encoded_stream);
		fclose(input);
		
		free(vector);
	}
	
	closedir(testvectors);
	
	return 0;
}

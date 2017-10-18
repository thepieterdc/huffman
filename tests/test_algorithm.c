/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <dirent.h>
#include <string.h>
#include "test_algorithm.h"
#include "test_unit.h"
#include "../src/util/logging.h"

#define TEST_ALGORITHM_TESTVECTORS "./tests/testvectors/"

char *test_huffman_algorithm(_huffmanfunction encoder, _huffmanfunction decoder) {
	DIR *testvectors = opendir(TEST_ALGORITHM_TESTVECTORS);
	assertThat(testvectors != NULL);
	
	struct dirent *dp;
	while ((dp = readdir(testvectors)) != NULL) {
		if (dp->d_type == DT_REG) {
			string ext = strrchr(dp->d_name, '.');
			if(!ext || !str_equals(ext, ".txt")) {
				continue;
			}
		}
		
		char *vector = str_concat(TEST_ALGORITHM_TESTVECTORS, dp->d_name);
		
		FILE *input = fopen(vector, "rb");
		assertThat(input != NULL);

		char *encoded_buf;
		size_t encoded_size;
		FILE *encoded = open_memstream(&encoded_buf, &encoded_size);

		char *decoded_buf;
		size_t decoded_size;
		FILE *decoded = open_memstream(&decoded_buf, &decoded_size);
		
		encoder(input, encoded);
//		decoder(encoded, decoded);
		
		//* TODO TEST decoded */
		
		fclose(input);
	}
	
	closedir(testvectors);
	
	return 0;
}

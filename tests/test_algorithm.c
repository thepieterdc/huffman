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
#include "../src/util/errors.h"

#define TEST_ALGORITHM_TESTVECTORS "./tests/testvectors/"

char *test_huffman_algorithm(_huffmanfunction encode, _huffmanfunction decode) {
	DIR *testvectors = opendir(TEST_ALGORITHM_TESTVECTORS);
	assertThat(testvectors != NULL);
	
	struct dirent *dp;
	while ((dp = readdir(testvectors)) != NULL) {
		string ext = strrchr(dp->d_name, '.');
		if (ext && str_equals(ext, ".in")) {
			
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
			
			FILE *raw = fopen(vector, "rb");
			assertThat(raw != NULL);
			
			fseek(raw, 0, SEEK_END);
			size_t raw_size = (size_t) ftell(raw);
			fseek(raw, 0, SEEK_SET);
			
			char raw_buffer[raw_size + 1];
			size_t last = fread(raw_buffer, sizeof(char), raw_size, raw);
			raw_buffer[last] = '\0';
			
			assertThat(raw_size == decoded_size);
			assertThat(str_equals(decoded, raw_buffer));

			fclose(raw);
			
			free(decoded);
			free(encoded);
			
			free(vector);
		}
	}
	
	closedir(testvectors);
	
	return 0;
}

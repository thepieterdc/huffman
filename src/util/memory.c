/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "errors.h"
#include "logging.h"
#include "memory.h"

void *callocate(size_t amount, size_t size) {
	void *ret = calloc(amount, size);
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	}
	return ret;
}

void *mallocate(size_t size) {
	void *ret = malloc(size);
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	}
	return ret;
}

void *reallocate(void *block, size_t size) {
	void *ret = realloc(block, size);
	if (!ret) {
		free(block);
		error(ERROR_MALLOC_FAILED);
	}
	return ret;
}
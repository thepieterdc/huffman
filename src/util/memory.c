/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdlib.h>
#include "errors.h"
#include "logging.h"
#include "memory.h"

void *callocate(const size_t amount, const size_t size) {
	void *ret = calloc(amount, size);
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	}
	return ret;
}

void *mallocate(const size_t size) {
	void *ret = malloc(size);
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	}
	return ret;
}

void *reallocate(void *block, const size_t size) {
	void *ret = realloc(block, size);
	if (!ret) {
		free(block);
		error(ERROR_MALLOC_FAILED);
	}
	return ret;
}
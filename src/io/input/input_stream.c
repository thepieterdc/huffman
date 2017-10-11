/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "input_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"

size_t is_count(input_stream *is) {
	return is->buffer->size;
}

input_stream *is_create() {
	input_stream *ret = (input_stream *) malloc(sizeof(input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->buffer = queue_create();
	}
	return ret;
}

void is_feed(input_stream *is, void *data) {
	queue_push(is->buffer, data);
}

void is_free(input_stream *is) {
	queue_free(is->buffer);
	free(is);
}

void *is_read(input_stream *is) {
	return queue_pop(is->buffer);
}
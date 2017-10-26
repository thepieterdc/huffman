/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "input_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"
#include "../../util/memory.h"

size_t is_count(input_stream *is) {
	return is->buffer->size;
}

input_stream *is_create() {
	input_stream *ret = (input_stream *) mallocate(sizeof(input_stream));
	ret->buffer = queue_create();
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
	if (is->buffer->size == 0) {
		error(ERROR_END_OF_INPUT);
	}
	return queue_pop(is->buffer);
}
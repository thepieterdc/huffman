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
	return is->size - is->cursor;
}

input_stream *is_create() {
	return (input_stream *) callocate(1, sizeof(input_stream));
}

void is_feed(input_stream *is, byte data) {
	if (is->size == INPUT_BUFFER_SIZE) {
		error(ERROR_INPUT_BUFFER_FULL);
	}
	is->buffer[is->size++] = data;
}

byte is_read(input_stream *is) {
	if (is->size == is->cursor) {
		error(ERROR_END_OF_INPUT);
	}
	return is->buffer[is->cursor++];
}
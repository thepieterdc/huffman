/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "output_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"
#include "../../datatypes/bit.h"

size_t os_count(output_stream *os) {
	return os->buffer->size;
}

output_stream *os_create(FILE *channel) {
	output_stream *ret = (output_stream *) malloc(sizeof(output_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->buffer = queue_create();
		ret->channel = channel;
	}
	return ret;
}

void os_feed(output_stream *os, void *data) {
	queue_push(os->buffer, data);
}

void os_flush(output_stream *os) {
	size_t amt = os_count(os);
	for (size_t i = 0; i < amt; ++i) {
		fprintf(os->channel, "%c", (byte) queue_pop(os->buffer));
	}
	fflush(os->channel);
}

void os_free(output_stream *os) {
	queue_free(os->buffer);
	
	if (os->channel) {
		fclose(os->channel);
	}
	
	free(os);
}
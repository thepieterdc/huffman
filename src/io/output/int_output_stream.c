/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "int_output_stream.h"
#include "../../util/errors.h"
#include "../../util/logging.h"
#include "output_stream.h"

size_t ios_count(int_output_stream *ios) {
	return os_count(ios->stream);
}

int_output_stream *ios_create(FILE *channel) {
	int_output_stream *ret = (int_output_stream *) malloc(sizeof(int_output_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->stream = os_create(channel);
	}
	return ret;
}

void ios_feed(int_output_stream *ios, int number) {
	os_feed(ios->stream, (void *) number);
}

void ios_flush(int_output_stream *ios) {
	size_t amt = ios_count(ios);
	for (size_t i = 0; i < amt; ++i) {
		fprintf(ios->stream->channel, "%d", (int) queue_pop(ios->stream->buffer));
	}
	fflush(ios->stream->channel);
}

void ios_free(int_output_stream *ios) {
	os_free(ios->stream);
	free(ios);
}
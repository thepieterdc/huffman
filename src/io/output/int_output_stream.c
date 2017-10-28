/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "int_output_stream.h"
#include "output_stream.h"
#include "../../util/memory.h"

size_t ios_count(int_output_stream *ios) {
	return ios->stream->buffer_size;
}

int_output_stream *ios_create(FILE *channel) {
	int_output_stream *ret = (int_output_stream *) mallocate(sizeof(int_output_stream));
	ret->stream = os_create(channel);
	return ret;
}

void ios_feed(int_output_stream *ios, int number) {
	os_feed(ios->stream, (byte) number);
}

void ios_flush(int_output_stream *ios) {
	for (size_t i = 0; i < ios->stream->buffer_size; ++i) {
		fprintf(ios->stream->channel, "%d", ios->stream->buffer[i]);
	}
	os_flush(ios->stream);
}

void ios_free(int_output_stream *ios) {
	os_free(ios->stream);
	free(ios);
}
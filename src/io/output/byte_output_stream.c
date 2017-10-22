/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "byte_output_stream.h"
#include "output_stream.h"
#include "../../util/memory.h"

size_t byos_count(byte_output_stream *bos) {
	return os_count(bos->stream);
}

byte_output_stream *byos_create(FILE *channel) {
	byte_output_stream *ret = (byte_output_stream *) mallocate(sizeof(byte_output_stream));
	ret->stream = os_create(channel);
	return ret;
}

void byos_feed(byte_output_stream *bos, byte b) {
	os_feed(bos->stream, (void *) b);
}

void byos_flush(byte_output_stream *bos) {
	size_t amt = byos_count(bos);
	for (size_t i = 0; i < amt; ++i) {
		fprintf(bos->stream->channel, "%c", (byte) queue_pop(bos->stream->buffer));
	}
	fflush(bos->stream->channel);
}

void byos_free(byte_output_stream *bos) {
	os_free(bos->stream);
	free(bos);
}
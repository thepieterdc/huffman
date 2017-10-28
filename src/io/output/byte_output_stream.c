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
	return bos->stream->buffer_size;
}

byte_output_stream *byos_create(FILE *channel) {
	byte_output_stream *ret = (byte_output_stream *) mallocate(sizeof(byte_output_stream));
	ret->stream = os_create(channel);
	return ret;
}

void byos_feed(byte_output_stream *bos, byte b) {
	os_feed(bos->stream, b);
}

void byos_flush(byte_output_stream *bos) {
	os_flush(bos->stream);
}

void byos_free(byte_output_stream *bos) {
	os_free(bos->stream);
	free(bos);
}
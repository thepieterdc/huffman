/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "byte_input_stream.h"
#include "../../util/errors.h"
#include "../../util/logging.h"

void byis_consume(byte_input_stream *bis) {
	int c;
	while ((c = getc(bis->channel)) != EOF) {
		byis_feed(bis, (byte) c);
	}
}

size_t byis_count(byte_input_stream *bis) {
	return is_count(bis->stream);
}

byte_input_stream *byis_create(FILE *channel) {
	byte_input_stream *ret = (byte_input_stream *) malloc(sizeof(byte_input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->channel = channel;
		ret->stream = is_create();
	}
	return ret;
}

void byis_feed(byte_input_stream *bis, byte b) {
	is_feed(bis->stream, (void *) b);
}

void byis_free(byte_input_stream *bis) {
	is_free(bis->stream);
	if(bis->channel) {
		fclose(bis->channel);
	}
	free(bis);
}

byte byis_read(byte_input_stream *bis) {
	return (byte) is_read(bis->stream);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <memory.h>
#include "output_stream.h"
#include "../../datatypes/bit.h"
#include "../../util/memory.h"

/**
 * Clears the buffer.
 *
 * @param os the output stream
 */
static void os_clear(output_stream *os) {
	memset(os->buffer, '\0', sizeof(os->buffer));
	os->buffer_size = 0;
}

output_stream *os_create(FILE *channel) {
	output_stream *ret = (output_stream *) mallocate(sizeof(output_stream));
	ret->channel = channel;
	os_clear(ret);
	return ret;
}

void os_feed(output_stream *os, byte data) {
	if (os->buffer_size == OUTPUT_BUFFER_SIZE) {
		os_flush(os);
	}
	if (os->buffer_size < OUTPUT_BUFFER_SIZE - 1) {
		os->buffer[os->buffer_size++] = data;
	}
}

void os_flush(output_stream *os) {
	for (size_t i = 0; i < os->buffer_size; ++i) {
		fprintf(os->channel, "%c", os->buffer[i]);
	}
	fflush(os->channel);
	os_clear(os);
}

void os_free(output_stream *os) {
	if (os->channel) {
		fclose(os->channel);
	}
	free(os);
}
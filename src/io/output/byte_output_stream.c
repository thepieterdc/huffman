/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <memory.h>
#include "byte_output_stream.h"
#include "../../util/memory.h"

/**
 * Clears the buffer.
 *
 * @param os the output stream
 */
static void byos_clear(byte_output_stream *byos) {
	memset(byos->buffer, '\0', sizeof(byos->buffer));
	byos->buffer_size = 0;
}

byte_output_stream *byos_create(FILE *channel) {
	byte_output_stream *ret = (byte_output_stream *) mallocate(sizeof(byte_output_stream));
	ret->channel = channel;
	byos_clear(ret);
	return ret;
}

void byos_feed(byte_output_stream *byos, byte data) {
	if (byos->buffer_size == OUTPUT_BUFFER_SIZE) {
		byos_flush(byos);
	}
	byos->buffer[byos->buffer_size++] = data;
}

void byos_flush(byte_output_stream *byos) {
	if(byos->buffer_size > 0) {
		fwrite(byos->buffer, 1, byos->buffer_size, byos->channel);
	}
	byos_clear(byos);
}

void byos_free(byte_output_stream *byos) {
	if (byos->channel) {
		fclose(byos->channel);
	}
	free(byos);
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include <memory.h>
#include "byte_input_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"
#include "../../util/memory.h"

/**
 * Expands or clears the internal buffer if necessary.
 *
 * @param byis
 */
static void buffer_expand(byte_input_stream *byis) {
	if (byis->buffer_size == byis->max_buffer_size) {
		if (byis->retain) {
			byis->max_buffer_size *= 2;
			byis->buffer = (byte *) reallocate(byis->buffer, byis->max_buffer_size);
		} else {
			byis->buffer_size = 0;
			memset(byis->buffer, '\0', byis->max_buffer_size);
		}
	}
}

byte_input_stream *byis_create(FILE *channel, bool retain) {
	byte_input_stream *ret = (byte_input_stream *) callocate(1, sizeof(byte_input_stream));
	ret->buffer = (byte *) callocate(INPUT_BUFFER_SIZE, sizeof(byte));
	ret->channel = channel;
	ret->end = false;
	ret->max_buffer_size = INPUT_BUFFER_SIZE;
	ret->retain = retain;
	return ret;
}

void byis_feed_byte(byte_input_stream *byis, byte data) {
	buffer_expand(byis);
	byis->buffer[byis->buffer_size++] = data;
}

void byis_feed_stream(byte_input_stream *byis, FILE *stream) {
	buffer_expand(byis);
	byis->buffer_size += fread(byis->buffer + byis->buffer_size, sizeof(byte),
	                           byis->max_buffer_size - byis->buffer_size, stream);
}

void byis_free(byte_input_stream *byis) {
	free(byis->buffer);
	if (byis->channel) {
		fclose(byis->channel);
	}
	free(byis);
}

byte byis_read(byte_input_stream *byis) {
	if (byis->end) {
		error(ERROR_END_OF_INPUT);
	}
	
	if (byis->cursor == byis->buffer_size) {
		if (byis->channel) {
			byis_feed_stream(byis, byis->channel);
		}
		if (byis->cursor == byis->buffer_size) {
			byis->end = true;
			return '\0';
		}
	}
	return byis->buffer[byis->cursor++];
}
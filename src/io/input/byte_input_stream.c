/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdlib.h>
#include "byte_input_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"
#include "../../util/memory.h"

/**
 * Expands the buffer by overwriting its contents.
 *
 * @param byis the byte input stream
 */
static void buffer_expand_overwrite(byte_input_stream *byis) {
	/* Retain the last 2 bits to ensure these get never lost. */
	byis->buffer[0] = byis->buffer[byis->buffer_size - 2];
	byis->buffer[1] = byis->buffer[byis->buffer_size - 1];
	byis->buffer_size = 2;
	byis->cursor = 0;
}

/**
 * Expands the buffer by retaining its contents.
 *
 * @param byis the byte input stream
 */
static void buffer_expand_retain(byte_input_stream *byis) {
	/* Prevents allocating enormous amounts of memory for large files. */
	if (byis->max_buffer_size <= GIBIBYTE(2)) {
		byis->max_buffer_size *= 2;
	} else {
		byis->max_buffer_size += GIBIBYTE(1);
	}
	byis->buffer = (byte *) reallocate(byis->buffer, byis->max_buffer_size);
}

void byis_consume(byte_input_stream *byis) {
	if(byis->buffer_size == byis->max_buffer_size) {
		size_t read = 0;
		do {
			byis->expandFn(byis);
			read = fread_unlocked(byis->buffer + byis->buffer_size, sizeof(byte),
			                       byis->max_buffer_size - byis->buffer_size, byis->channel);
			byis->buffer_size += read;
		} while (read != 0);
	}
}

byte_input_stream *byis_create(FILE *channel, bool retain) {
	byte_input_stream *ret = (byte_input_stream *) callocate(1, sizeof(byte_input_stream));
	ret->buffer = (byte *) callocate(INPUT_BUFFER_SIZE + 2, sizeof(byte));
	ret->channel = channel;
	ret->max_buffer_size = INPUT_BUFFER_SIZE + 2;
	ret->expandFn = (_input_buffer_expand_function) (retain ? buffer_expand_retain : buffer_expand_overwrite);
	
	if (channel) {
		flockfile(channel);
		ret->buffer_size = fread_unlocked(ret->buffer, sizeof(byte), ret->max_buffer_size, channel);
	}
	return ret;
}

void byis_free(byte_input_stream *byis) {
	if (byis->channel) {
		funlockfile(byis->channel);
	}
	free(byis->buffer);
	free(byis);
}

byte byis_read(byte_input_stream *byis) {
	if (byis->cursor < byis->buffer_size - 2) {
		return byis->buffer[byis->cursor++];
	}
	
	/* The internal buffer is fully used. */
	if (byis->cursor == byis->buffer_size - 2) {
		byis->expandFn(byis);
		byis->buffer_size += fread_unlocked(byis->buffer + byis->buffer_size, sizeof(byte),
		                                    byis->max_buffer_size - byis->buffer_size, byis->channel);
	}
	
	/* The input stream is empty. */
	if (byis->buffer_size == 0) {
		error(ERROR_END_OF_INPUT);
	}
	
	return byis->buffer[byis->cursor++];
}
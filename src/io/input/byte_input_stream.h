/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_INPUT_BYTEINPUTSTREAM_H
#define HUFFMAN_IO_INPUT_BYTEINPUTSTREAM_H

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include "../../datatypes/bit.h"
#include "../../util/binary.h"

#define INPUT_BUFFER_SIZE MEBIBYTE(2)

/**
 * A byte input stream.
 */
struct byte_input_stream;

/**
 * A function that expands the buffer.
 */
typedef void (*_input_buffer_expand_function)(struct byte_input_stream *);

typedef struct byte_input_stream {
	byte *buffer;
	FILE *channel;
	size_t cursor;
	size_t buffer_size;
	size_t max_buffer_size;
	_input_buffer_expand_function expandFn;
} byte_input_stream;

/**
 * Reads the entire input stream.
 *
 * @param byis the byte input stream to consume
 */
void byis_consume(byte_input_stream *byis);

/**
 * Creates a new byte input stream.
 *
 * @param channel the encapsulated stream to feed off
 * @param retain false to clear the buffer when full, true to expand it
 * @return the created byte input stream
 */
byte_input_stream *byis_create(FILE *channel, bool retain);

/**
 * Frees the memory allocated by the byte input stream.
 *
 * @param byis the the input stream
 */
void byis_free(byte_input_stream *byis);

/**
 * Reads a byte from the input stream.
 *
 * @param byis the byte input stream
 * @return the byte read
 */
byte byis_read(byte_input_stream *byte);

/**
 * Reads a byte from the input stream without checking for overflows.
 *
 * @param byis the byte input stream
 * @return the byte read
 */
#define byis_read_unsafe(byis) (byte) ((byis)->buffer[(byis)->cursor++])

#endif /* HUFFMAN_IO_INPUT_BYTEINPUTSTREAM_H */
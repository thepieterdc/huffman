/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_INPUT_BYTEINPUTSTREAM_H
#define HUFFMAN_IO_INPUT_BYTEINPUTSTREAM_H

#include <stdio.h>
#include <stdbool.h>
#include "../../datatypes/bit.h"

#define INPUT_BUFFER_SIZE 4096

/**
 * A byte input stream.
 */
typedef struct {
	byte *buffer;
	FILE *channel;
	size_t cursor;
	size_t buffer_size;
	size_t max_buffer_size;
	bool retain;
} byte_input_stream;

/**
 * Creates a new byte input stream.
 *
 * @param channel the encapsulated stream to feed off
 * @param retain false to clear the buffer when full, true to expand it
 * @return the created byte input stream
 */
byte_input_stream *byis_create(FILE *channel, bool retain);

/**
 * Adds a byte to the input stream.
 *
 * @param byis the input stream
 * @param data the byte to feed
 */
void byis_feed_byte(byte_input_stream *byis, byte data);

/**
 * Consumes bytes from a stream to the input stream.
 *
 * @param byis the input stream
 * @param stream the stream to consume
 */
void byis_feed_stream(byte_input_stream *byis, FILE *stream);

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
byte byis_read(byte_input_stream *byis);

#endif /* HUFFMAN_IO_INPUT_BYTEINPUTSTREAM_H */
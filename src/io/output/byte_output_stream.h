/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_BYTEOUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_BYTEOUTPUTSTREAM_H

#include <stdio.h>
#include <stdbool.h>
#include "../../datatypes/bit.h"

#define OUTPUT_BUFFER_SIZE 4096

/**
 * A byte output stream.
 */
typedef struct {
	byte buffer[OUTPUT_BUFFER_SIZE + 1];
	size_t buffer_size;
	FILE *channel;
} byte_output_stream;

/**
 * Creates a new byte output stream.
 *
 * @param channel the output channel to flush to
 * @return the created byte output stream
 */
byte_output_stream *byos_create(FILE *channel);

/**
 * Adds data to the output stream.
 *
 * @param byos the output stream
 * @param data the data to feed
 */
void byos_feed(byte_output_stream *byos, byte data);

/**
 * Flushes the output buffer.
 *
 * @param os the output stream
 * @return the value read
 */
void byos_flush(byte_output_stream *byos);

/**
 * Frees the memory allocated by the output stream.
 *
 * @param byos the byte output stream
 */
void byos_free(byte_output_stream *byos);

#endif /* HUFFMAN_IO_OUTPUT_BYTEOUTPUTSTREAM_H */
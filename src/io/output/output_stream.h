/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_OUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_OUTPUTSTREAM_H

#include <stdio.h>
#include <stdbool.h>
#include "../../datatypes/bit.h"

#define OUTPUT_BUFFER_SIZE 4096

/**
 * An input stream.
 */
typedef struct {
	byte buffer[OUTPUT_BUFFER_SIZE + 1];
	size_t buffer_size;
	FILE *channel;
} output_stream;

/**
 * Creates a new output stream.
 *
 * @param channel the output channel to flush to
 * @return the created output stream
 */
output_stream *os_create(FILE *channel);

/**
 * Adds data to the output stream.
 *
 * @param os the output stream
 * @param data the data to feed
 */
void os_feed(output_stream *os, byte data);

/**
 * Flushes the output buffer.
 *
 * @param os the output stream
 * @return the value read
 */
void os_flush(output_stream *os);

/**
 * Frees the memory allocated by the output stream.
 *
 * @param os the output stream
 */
void os_free(output_stream *os);

#endif /* HUFFMAN_IO_OUTPUT_OUTPUTSTREAM_H */
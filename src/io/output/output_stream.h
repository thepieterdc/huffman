/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_OUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_OUTPUTSTREAM_H

#include <stdio.h>
#include <stdbool.h>
#include "../../datastructures/queue.h"

/**
 * An input stream.
 */
typedef struct {
	queue *buffer;
	FILE *channel;
} output_stream;

/**
 * Gets the amount of items in the output stream buffer.
 *
 * @param os the output stream
 * @return the amount of items in the output stream buffer
 */
size_t os_count(output_stream *os);

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
void os_feed(output_stream *os, void *data);

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
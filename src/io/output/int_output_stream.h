/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_INT_OUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_INT_OUTPUTSTREAM_H

#include <stdio.h>
#include "output_stream.h"

/**
 * An output stream for integers.
 */
typedef struct {
	output_stream *stream;
} int_output_stream;

/**
 * Gets the amount of items in the int output stream buffer.
 *
 * @param ios the int output stream
 * @return the amount of items in the int output stream buffer
 */
size_t ios_count(int_output_stream *ios);

/**
 * Creates a new output stream for integers.
 *
 * @param channel the output channel to flush to
 * @return the created int output stream
 */
int_output_stream *ios_create(FILE *channel);

/**
 * Feeds the stream with one integer.
 *
 * @param ios the int output stream
 * @param number the integer to feed
 */
void ios_feed(int_output_stream *ios, int number);

/**
 * Flushes the buffer of the output stream.
 *
 * @param ios the int output stream
 */
void ios_flush(int_output_stream *ios);

/**
 * Frees the memory allocated by the int output stream.
 *
 * @param ios the int output stream
 */
void ios_free(int_output_stream *ios);

#endif /* HUFFMAN_IO_OUTPUT_INT_OUTPUTSTREAM_H */
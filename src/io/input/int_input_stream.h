/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_INPUT_INT_INPUTSTREAM_H
#define HUFFMAN_IO_INPUT_INT_INPUTSTREAM_H

#include <stdio.h>
#include "../../datastructures/queue.h"
#include "input_stream.h"

/**
 * An input stream for integers.
 */
typedef struct {
	FILE *channel;
	input_stream *stream;
} int_input_stream;

/**
 * Consumes the entire input channel and saves it to the buffer.
 *
 * @param iis the int input stream
 */
void iis_consume(int_input_stream *iis);

/**
 * Gets the amount of items in the int input stream buffer.
 *
 * @param is the int input stream
 * @return the amount of items in the int input stream buffer
 */
size_t iis_count(int_input_stream *iis);

/**
 * Creates a new input stream for integers.
 *
 * @param channel the data to feed the stream from
 * @return the created int input stream
 */
int_input_stream *iis_create(FILE *channel);

/**
 * Feeds the stream with one integer.
 *
 * @param iis the int input stream
 * @param number the integer to feed
 */
void iis_feed(int_input_stream *iis, int number);

/**
 * Frees the memory allocated by the int input stream.
 *
 * @param iis the int input stream
 */
void iis_free(int_input_stream *iis);

/**
 * Reads one integer from the integer input stream
 *
 * @param iis the int input stream
 * @return the integer
 */
int iis_read(int_input_stream *iis);

#endif /* HUFFMAN_IO_INPUT_INT_INPUTSTREAM_H */
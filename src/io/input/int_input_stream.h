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
	input_stream *stream;
} int_input_stream;

/**
 * Creates a new input stream for integers.
 *
 * @param channel the data to feed the stream from
 * @return the created int input stream
 */
int_input_stream *iis_create(FILE *channel);

/**
 * Frees the memory allocated by the int input stream.
 *
 * @param iis the int input stream
 */
void iis_free(int_input_stream *iis);

#endif /* HUFFMAN_IO_INPUT_INT_INPUTSTREAM_H */
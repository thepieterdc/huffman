/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_INPUT_BYTE_INPUTSTREAM_H
#define HUFFMAN_IO_INPUT_BYTE_INPUTSTREAM_H

#include <stdio.h>
#include "../../datastructures/queue.h"
#include "input_stream.h"
#include "../../datatypes/bit.h"

/**
 * An input stream for bytes.
 */
typedef struct {
	FILE *channel;
	input_stream *stream;
} byte_input_stream;

/**
 * Consumes the entire input channel and saves it to the buffer.
 *
 * @param bis the byte input stream
 */
void byis_consume(byte_input_stream *bis);

/**
 * Gets the amount of items in the byte input stream buffer.
 *
 * @param bis the byte input stream
 * @return the amount of items in the byte input stream buffer
 */
size_t byis_count(byte_input_stream *bis);

/**
 * Creates a new input stream for bytes.
 *
 * @param channel the data to feed the stream from
 * @return the created byte input stream
 */
byte_input_stream *byis_create(FILE *channel);

/**
 * Feeds the stream with one byte.
 *
 * @param bis the byte input stream
 * @param b the byte to feed
 */
void byis_feed(byte_input_stream *bis, byte b);

/**
 * Frees the memory allocated by the byte input stream.
 *
 * @param bis the byte input stream
 */
void byis_free(byte_input_stream *bis);

/**
 * Reads one byte from the byte input stream
 *
 * @param bis the byte input stream
 * @return the byte
 */
byte byis_read(byte_input_stream *bis);

#endif /* HUFFMAN_IO_INPUT_BYTE_INPUTSTREAM_H */
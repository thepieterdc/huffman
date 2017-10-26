/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_INPUT_INPUTSTREAM_H
#define HUFFMAN_IO_INPUT_INPUTSTREAM_H

#include <stdio.h>
#include <stdbool.h>
#include "../../datastructures/queue.h"
#include "../../datatypes/bit.h"

#define INPUT_BUFFER_SIZE 4096

/**
 * An input stream.
 */
typedef struct {
	byte buffer[INPUT_BUFFER_SIZE];
	size_t cursor;
	size_t size;
} input_stream;

/**
 * Gets the amount of items in the input stream buffer.
 *
 * @param is the input stream
 * @return the amount of items in the input stream buffer
 */
size_t is_count(input_stream *is);

/**
 * Creates a new input stream.
 *
 * @return the created input stream
 */
input_stream *is_create();

/**
 * Adds data to the input stream.
 *
 * @param is the input stream
 * @param data the data to feed
 */
void is_feed(input_stream *is, byte data);

/**
 * Frees the memory allocated by the input stream.
 *
 * @param is the input stream
 */
void is_free(input_stream *is);

/**
 * Reads a value from the input stream, removing it from the buffer.
 *
 * @param is the input stream
 * @return the value read
 */
byte is_read(input_stream *is);

#endif /* HUFFMAN_IO_INPUT_INPUTSTREAM_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_IO_OUTPUT_BYTE_OUTPUTSTREAM_H
#define HUFFMAN_IO_OUTPUT_BYTE_OUTPUTSTREAM_H

#include "output_stream.h"
#include "../../datatypes/bit.h"

/**
 * An output stream for bytes.
 */
typedef struct {
	output_stream *stream;
} byte_output_stream;

/**
 * Gets the amount of items in the byte output stream buffer.
 *
 * @param bos the byte output stream
 * @return the amount of items in the byte output stream buffer
 */
size_t byos_count(byte_output_stream *bos);

/**
 * Creates a new output stream for bytes.
 *
 * @param channel the data to feed the stream from
 * @return the created byte output stream
 */
byte_output_stream *byos_create(FILE *channel);

/**
 * Feeds the stream with one byte.
 *
 * @param bos the byte output stream
 * @param b the byte to feed
 */
void byos_feed(byte_output_stream *bos, byte b);

/**
 * Flushes the output buffer.
 *
 * @param bos the byte output stream
 */
void byos_flush(byte_output_stream *bos);

/**
 * Frees the memory allocated by the byte output stream.
 *
 * @param bos the byte output stream
 */
void byos_free(byte_output_stream *bos);

#endif /* HUFFMAN_IO_OUTPUT_BYTE_OUTPUTSTREAM_H */
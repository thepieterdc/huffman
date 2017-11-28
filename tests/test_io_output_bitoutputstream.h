/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_OUTPUT_BITOUTPUTSTREAM_H
#define HUFFMAN_TEST_IO_OUTPUT_BITOUTPUTSTREAM_H

/** Tests bos_create(), bos_free(). */
const char *test_io_bos_create_free();

/** Tests bos_feed_bit(), bos_flush(). */
const char *test_io_bos_feed_bit_flush();

/** Tests bos_feed_bit(), bos_pad(), bos_flush(). */
const char *test_io_bos_feed_bit_pad_flush();

#endif /* HUFFMAN_TEST_IO_OUTPUT_BITOUTPUTSTREAM_H */
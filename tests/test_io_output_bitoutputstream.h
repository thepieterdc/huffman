/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_OUTPUT_BITOUTPUTSTREAM_H
#define HUFFMAN_TEST_IO_OUTPUT_BITOUTPUTSTREAM_H

/** Tests bos_create(), bos_free(). */
char *test_io_bos_create_free();

/** Tests bos_feed_bit(), bos_flush(), bos_count(). */
char *test_io_bos_feed_bit_flush_count();

/** Tests bos_feed_bit(), bos_pad(), bos_flush(), bos_count(). */
char *test_io_bos_feed_bit_pad_flush_count();

/** Tests bos_feed_byte(), bos_flush(), bos_count(). */
char *test_io_bos_feed_byte_flush_count();

#endif /* HUFFMAN_TEST_IO_OUTPUT_BITOUTPUTSTREAM_H */
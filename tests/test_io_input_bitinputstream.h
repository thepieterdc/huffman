/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_INPUT_BITINPUTSTREAM_H
#define HUFFMAN_TEST_IO_INPUT_BITINPUTSTREAM_H

/** Tests bis_create(), bis_free(). */
char *test_io_bis_create_free();

/** Tests bis_consume(), bis_read_bit(), bis_count(). */
char *test_io_bis_consume_read_bit_count();

/** Tests bis_feed_bit(), bis_read_bit(), bis_count(). */
char *test_io_bis_feed_bit_read_bit_count();

/** Tests bis_feed_byte(), bis_read_byte(), bis_count(). */
char *test_io_bis_feed_byte_read_byte_count();

#endif /* HUFFMAN_TEST_IO_INPUT_BITINPUTSTREAM_H */
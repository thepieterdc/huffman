/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_INPUT_INTINPUTSTREAM_H
#define HUFFMAN_TEST_IO_INPUT_INTINPUTSTREAM_H

/** Tests iis_create(), iis_free(). */
char *test_io_iis_create_free();

/** Tests iis_consume(), iis_read(), iis_count(). */
char *test_io_iis_consume_read_count();

/** Tests iis_feed(), iis_read(), iis_count(). */
char *test_io_iis_feed_read_count();

#endif /* HUFFMAN_TEST_IO_INPUT_INTINPUTSTREAM_H */
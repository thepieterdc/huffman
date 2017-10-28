/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_INPUT_BYTEINPUTSTREAM_H
#define HUFFMAN_TEST_IO_INPUT_BYTEINPUTSTREAM_H

/** Tests byis_create(), byis_free(). */
char *test_io_byis_create_free();

/** Tests byis_feed_byte(), byis_read(). */
char *test_io_byis_feed_byte_read();

/** Tests byis_feed_stream(), byis_read(). */
char *test_io_byis_feed_stream_read();

#endif /* HUFFMAN_TEST_IO_INPUT_BYTEINPUTSTREAM_H */
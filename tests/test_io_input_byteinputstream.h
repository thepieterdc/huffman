/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_INPUT_BYTEINPUTSTREAM_H
#define HUFFMAN_TEST_IO_INPUT_BYTEINPUTSTREAM_H

/** Tests byis_create(), byis_free(). */
char *test_io_byis_create_free();

/** Tests byis_consume(), byis_read(), byis_count(), byis_empty(). */
char *test_io_byis_consume_read_count_empty();

/** Tests byis_feed(), byis_read(), byis_count(), byis_empty(). */
char *test_io_byis_feed_read_count_empty();

#endif /* HUFFMAN_TEST_IO_INPUT_BYTEINPUTSTREAM_H */
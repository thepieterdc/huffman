/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_INPUT_BITINPUTSTREAM_H
#define HUFFMAN_TEST_IO_INPUT_BITINPUTSTREAM_H

/** Tests bis_create(), bis_free(). */
char *test_io_bis_create_free();

/** Tests bis_read_bit(), bis_count(), bis_clear_buffer(). */
char *test_io_bis_read_bit_count_clear_buffer();

/** Tests bis_read_byte(), bis_count(). */
char *test_io_bis_read_byte_count();

#endif /* HUFFMAN_TEST_IO_INPUT_BITINPUTSTREAM_H */
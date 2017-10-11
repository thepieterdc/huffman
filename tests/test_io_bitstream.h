/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_IO_BITSTREAM_H
#define HUFFMAN_TEST_IO_BITSTREAM_H

/** Tests bs_create(), bs_free(). */
char *test_bs_create_free();

/** Tests bs_add_bit(). */
char *test_bs_add_bit();

/** Tests bs_add_byte(). */
char *test_bs_add_byte();

#endif /* HUFFMAN_TEST_IO_BITSTREAM_H */
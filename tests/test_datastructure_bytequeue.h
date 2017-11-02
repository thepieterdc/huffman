/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_TEST_DATASTRUCTURE_BYTEQUEUE_H
#define HUFFMAN_TEST_DATASTRUCTURE_BYTEQUEUE_H

/** Tests: byte_queue_create(), byte_queue_free(). */
const char *test_byte_queue_create_free();

/** Tests: byte_queue_empty(). */
const char *test_byte_queue_empty();

/** Tests: byte_queue_push(), byte_queue_peek(), byte_queue_pop(). */
const char *test_byte_queue_push_peek_pop();

#endif /* HUFFMAN_TEST_DATASTRUCTURE_BYTEQUEUE_H */
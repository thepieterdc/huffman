/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_ERRORS_H
#define HUFFMAN_UTIL_ERRORS_H

#define ERROR_MALLOC_FAILED 0
#define ERROR_INDEX_OUT_OF_BOUNDS 1
#define ERROR_EMPTY_HEAP 2
#define ERROR_END_OF_INPUT 3
#define ERROR_EMPTY_BYTEQUEUE 4
#define ERROR_INVALID_INPUT 5

/**
 * Contains all error messages; keys are defined above.
 */
extern const char *_error_messages[];

#endif /* HUFFMAN_UTIL_ERRORS_H */
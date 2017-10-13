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
#define ERROR_ARGUMENT_ALGORITHM 3
#define ERROR_ARGUMENT_MODE 4

/**
 * Contains all error messages; keys are defined above.
 */
extern char *_error_messages[];

#endif /* HUFFMAN_UTIL_ERRORS_H */
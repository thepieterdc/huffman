/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_LOGGING_H
#define HUFFMAN_UTIL_LOGGING_H

#include "stdbool.h"

/**
 * Throws an error message to stderr.
 *
 * @param code the error code
 * @param exit true to exit the program after throwing this error
 */
#ifndef IS_TEST
void error(int code);
#else
void error(char *msg);
#endif

/**
 * Shows an informational message to stdout.
 *
 * @param msg te message
 */
void info(char *msg);

/**
 * Shows a success message to stdout.
 *
 * @param msg te message
 */
void success(char *msg);

/**
 * Throws an warning message to stderr.
 *
 * @param msg te message
 */
void warning(char *msg);

#endif /* HUFFMAN_UTIL_LOGGING_H */
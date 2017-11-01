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
 */
void error(int code);

/**
 * Throws a custom error message to stderr.
 *
 * @param msg the error message
 * @param exit true to exit the program after throwing this error
 */
void error_custom(const char *msg, bool exit);

/**
 * Shows an informational message to stdout.
 *
 * @param msg te message
 */
void info(const char *msg);

/**
 * Shows a success message to stdout.
 *
 * @param msg te message
 */
void success(const char *msg);

/**
 * Throws an warning message to stderr.
 *
 * @param msg te message
 */
void warning(const char *msg);

#endif /* HUFFMAN_UTIL_LOGGING_H */
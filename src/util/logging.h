/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_LOGGING_H
#define HUFFMAN_UTIL_LOGGING_H

#include "stdarg.h"
#include "stdbool.h"

/**
 * Throws an error message to stderr.
 *
 * @param code the error code
 * @param exit true to exit the program after throwing this error
 */
void error(int code);

/**
 * Shows an informational message to stdout.
 *
 * @param format the formatted string
 */
void info(char *format, ...);

/**
 * Shows a success message to stdout.
 *
 * @param fmt the formatted string
 */
void success(char *format, ...);

/**
 * Throws an warning message to stderr.
 *
 * @param format the formatted string
 */
void warning(char *format, ...);

#endif /* HUFFMAN_UTIL_LOGGING_H */
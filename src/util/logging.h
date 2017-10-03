/**
 * Created by Pieter De Clercq.
 *
 * Project: ad3_huffman
 */

#ifndef AD3_HUFFMAN_UTIL_LOGGING_H
#define AD3_HUFFMAN_UTIL_LOGGING_H

#include "stdbool.h"

/**
 * Throws an error message to stderr.
 *
 * @param msg the message
 * @param exit true to exit the program after throwing this error
 */
//TODO errorcodes
void error(char* msg, bool exit);

/**
 * Shows an informational message to stdout.
 *
 * @param msg the message
 */
void info(char *msg);

/**
 * Shows a success message to stdout.
 *
 * @param msg the message
 */
void success(char *msg);

/**
 * Throws an warning message to stderr.
 *
 * @param msg the message
 */
void warning(char* msg);

#endif /* AD3_HUFFMAN_UTIL_LOGGING_H */
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "logging.h"
#include "string.h"

#define COLOUR_LOG_ERROR "\x1B[1;31m"
#define COLOUR_LOG_INFO "\x1B[36m"
#define COLOUR_LOG_SUCCESS "\x1B[32m"
#define COLOUR_LOG_WARNING "\x1B[1;33m"
#define COLOUR_LOG_CLEAR "\x1B[0m"

/**
 * Writes a log message.
 *
 * @param type the message type
 * @param colour the colour to display the message in
 * @param msg the message
 */
void write_message(FILE *channel, const char type[], const char colour[], string msg) {
	fprintf(channel, "%s[%s]%s %s\n", colour, type, COLOUR_LOG_CLEAR, msg);
	fflush(channel);
}

#ifndef IS_TEST
void error(int code) {
	write_message(stderr, "ERROR", COLOUR_LOG_ERROR, _error_messages[code]);
	exit(code + 100);
}
#else
void error(char *msg) {
	write_message(stderr, "ERROR", COLOUR_LOG_ERROR, msg);
}
#endif

void info(char *msg) {
#ifdef IS_DEBUG
	write_message(stdout, "INFO", COLOUR_LOG_INFO, msg);
#endif
}

void success(char *msg) {
#ifdef IS_DEBUG
	write_message(stdout, "OK", COLOUR_LOG_SUCCESS, msg);
#endif
}

void warning(char *msg) {
#ifdef IS_DEBUG
	write_message(stderr, "WARNING", COLOUR_LOG_WARNING, msg);
#endif
}
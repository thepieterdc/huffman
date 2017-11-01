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
void write_message(const char type[], const char colour[], const char *msg) {
	fprintf(stderr, "%s[%s]%s %s\n", colour, type, COLOUR_LOG_CLEAR, msg);
	fflush(stderr);
}

void error(const int code) {
	write_message("ERROR", COLOUR_LOG_ERROR, _error_messages[code]);
	exit(code + 100);
}

void error_custom(const char *msg, const bool e) {
	write_message("ERROR", COLOUR_LOG_ERROR, msg);
	if (e) {
		exit(100);
	}
}

void info(const char *msg) {
	write_message("INFO", COLOUR_LOG_INFO, msg);
}

void success(const char *msg) {
	write_message("OK", COLOUR_LOG_SUCCESS, msg);
}

void warning(const char *msg) {
	write_message("WARNING", COLOUR_LOG_WARNING, msg);
}
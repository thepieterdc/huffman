/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "int_input_stream.h"
#include "../../util/string.h"
#include "../../util/errors.h"
#include "../../util/logging.h"

void iis_consume(int_input_stream *iis) {
	int c;
	while ((c = getc(iis->channel)) != EOF) {
		iis_feed(iis, char_to_int((char) c));
	}
}

size_t iis_count(int_input_stream *iis) {
	return is_count(iis->stream);
}

int_input_stream *iis_create(FILE *channel) {
	int_input_stream *ret = (int_input_stream *) malloc(sizeof(int_input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->channel = channel;
		ret->stream = is_create();
	}
	return ret;
}

void iis_feed(int_input_stream *iis, int number) {
	is_feed(iis->stream, (void *) number);
}

void iis_free(int_input_stream *iis) {
	is_free(iis->stream);
	fclose(iis->channel);
	free(iis);
}

int iis_read(int_input_stream *iis) {
	return (int) is_read(iis->stream);
}
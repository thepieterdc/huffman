/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "input_stream.h"
#include "../../util/logging.h"
#include "../../util/errors.h"
#include "int_input_stream.h"

int_input_stream *iis_create(FILE *channel) {
	int_input_stream *ret = (int_input_stream *) malloc(sizeof(int_input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->stream = is_create(channel);
	}
	return ret;
}

void iis_free(int_input_stream *iis) {
	is_free(iis->stream);
	free(iis);
}
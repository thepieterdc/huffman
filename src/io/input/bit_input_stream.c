/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_input_stream.h"
#include "../../util/errors.h"
#include "../../util/logging.h"
//
//void byis_consume(byte_input_stream *bis) {
//	int c;
//	while ((c = getc(bis->channel)) != EOF) {
//		byis_feed(bis, (byte) c);
//	}
//}
//
//size_t byis_count(byte_input_stream *bis) {
//	return is_count(bis->stream);
//}

bit_input_stream *bis_create(FILE *channel) {
	bit_input_stream *ret = (bit_input_stream *) malloc(sizeof(bit_input_stream));
	if (!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->bytestream = byis_create(channel);
		ret->current_byte = 0;
		ret->curent_cursor = 0;
	}
	return ret;
}

//void byis_feed(byte_input_stream *bis, byte b) {
//	is_feed(bis->stream, (void *) b);
//}

void bis_free(bit_input_stream *bis) {
	byis_free(bis->bytestream);
	free(bis);
}

//byte byis_read(byte_input_stream *bis) {
//	return (byte) is_read(bis->stream);
//}
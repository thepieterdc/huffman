/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

/** Required to use unlocked IO and memory streams. */
#define _GNU_SOURCE

#include "common.h"
#include "../../io/output/bit_output_stream.h"

size_t huffman_finalize_input(bit_input_stream *in) {
	byte final_byte = in->current_byte;
	size_t final_cursor = in->current_cursor;
	size_t indicator = byis_read(in->stream);
	bis_flush(in);
	
	in->current_byte = final_byte;
	in->current_cursor = final_cursor;
	return indicator;
}

void huffman_prepare_output(FILE *out) {
	flockfile(out);

#ifdef IS_DEBUG
#ifndef IS_TEST
	setvbuf(out, NULL, _IONBF, OUTPUT_BUFFER_SIZE);
#endif
#else
	setvbuf(out, NULL, _IOFBF, OUTPUT_BUFFER_SIZE);
#endif
}
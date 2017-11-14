/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "common.h"

size_t huffman_finalize_input(bit_input_stream *in) {
	byte final_byte = in->current_byte;
	size_t final_cursor = in->current_cursor;
	size_t indicator = byis_read(in->stream);
	bis_flush(in);
	
	in->current_byte = final_byte;
	in->current_cursor = final_cursor;
	return indicator;
}
/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "bit_output_stream.h"
#include "../../util/memory.h"

/**
 * Prints the contents of the internal buffer.
 *
 * @param bos the bit output stream
 */
static void print_buffer(bit_output_stream *bos) {
	putc(bos->current_byte, bos->channel);
	bos->current_byte = 0;
	bos->current_cursor = 8;
}

bit_output_stream *bos_create(FILE *channel) {
	bit_output_stream *ret = (bit_output_stream *) mallocate(sizeof(bit_output_stream));
	ret->channel = channel;
	ret->current_byte = 0;
	ret->current_cursor = 8;
	return ret;
}

void bos_feed_bit(bit_output_stream *bos, bit b) {
	bos->current_byte |= (b << (--bos->current_cursor));
	if (bos->current_cursor == 0) {
		print_buffer(bos);
	}
}

void bos_feed_byte(bit_output_stream *bos, byte b) {
	if (bos->current_cursor == 8) {
		putc(b, bos->channel);
	} else {
		for (size_t i = 0; i < 8; ++i) {
			bos_feed_bit(bos, (bit) (b & (1 << (7 - i))) != 0);
		}
	}
}

void bos_feed_huffmancode(bit_output_stream *bos, huffman_code *hc) {
	for (size_t pad = 0; pad < hc->padding; ++pad) {
		bos_feed_bit(bos, 0);
	}
	
	if (hc->code == 0) return;
	
	uint_fast64_t mask = ((uint_fast64_t) 1) << 63;
	while ((mask > 0) && ((hc->code & mask) == 0)) mask >>= 1;
	
	do {
		bos_feed_bit(bos, (hc->code & mask) != 0);
		mask >>= 1;
	} while (mask > 0);
}

void bos_flush(bit_output_stream *bos) {
	if (bos->current_cursor != 8) {
		print_buffer(bos);
	}
	fflush(bos->channel);
}

void bos_free(bit_output_stream *bos) {
	if (bos->channel) {
		fclose(bos->channel);
	}
	free(bos);
}

size_t bos_pad(bit_output_stream *bos) {
	size_t padding = bos->current_cursor;
	print_buffer(bos);
	return padding;
}
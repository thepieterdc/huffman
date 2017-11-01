/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "byte_queue.h"
#include "../util/memory.h"
#include "../util/logging.h"
#include "../util/errors.h"

byte_queue *byte_queue_create() {
	byte_queue *q = (byte_queue *) mallocate(sizeof(byte_queue));
	q->size = 0;
	q->first = q->last = NULL;
	return q;
}

void byte_queue_empty(byte_queue *q) {
	byte_queue_item *cursor = q->first;
	byte_queue_item *next = NULL;
	
	for (size_t i = 0; i < q->size; ++i) {
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	q->size = 0;
}

void byte_queue_free(byte_queue *q) {
	byte_queue_empty(q);
	free(q);
}

byte byte_queue_peek(byte_queue *q) {
	if (q->first == NULL) {
		error(ERROR_EMPTY_BYTEQUEUE);
	}
	return q->first->data;
}

byte byte_queue_pop(byte_queue *q) {
	if (q->first == NULL) {
		error(ERROR_EMPTY_BYTEQUEUE);
	}
	
	byte_queue_item *first = q->first;
	byte ret = first->data;
	
	q->first = first->next;
	q->size--;
	free(first);
	
	return ret;
}

void byte_queue_push(byte_queue *q, byte data) {
	byte_queue_item *newitem = (byte_queue_item *) mallocate(sizeof(byte_queue_item));
	newitem->data = data;
	if (q->last != NULL) {
		q->last->next = newitem;
	} else {
		q->first = newitem;
	}
	q->last = newitem;
	q->size++;
}
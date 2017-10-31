/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "byte_queue.h"
#include "../util/memory.h"

byte_queue *queue_create() {
	byte_queue *q = (byte_queue *) mallocate(sizeof(byte_queue));
	q->size = 0;
	q->first = q->last = NULL;
	return q;
}

void queue_empty(byte_queue *q) {
	queue_item *cursor = q->first;
	queue_item *next = NULL;
	
	for (size_t i = 0; i < q->size; ++i) {
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	q->size = 0;
}

void queue_free(byte_queue *q) {
	queue_empty(q);
	free(q);
}

void *queue_peek(byte_queue *q) {
	if (q->first == NULL) {
		return NULL;
	}
	return q->first->data;
}

void *queue_pop(byte_queue *q) {
	if (q->first == NULL) {
		return NULL;
	}
	
	queue_item *first = q->first;
	void *ret = first->data;
	
	q->first = first->next;
	q->size--;
	free(first);
	
	return ret;
}

void queue_push(byte_queue *q, void *data) {
	queue_item *newitem = (queue_item *) mallocate(sizeof(queue_item));
	newitem->data = data;
	if (q->last != NULL) {
		q->last->next = newitem;
	} else {
		q->first = newitem;
	}
	q->last = newitem;
	q->size++;
}
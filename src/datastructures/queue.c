/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "queue.h"
#include "../util/memory.h"

queue *queue_create() {
	queue *q = (queue *) mallocate(sizeof(queue));
	q->size = 0;
	q->first = q->last = NULL;
	return q;
}

void queue_empty(queue *q) {
	queue_item *cursor = q->first;
	queue_item *next = NULL;
	
	for (size_t i = 0; i < q->size; ++i) {
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	q->size = 0;
}

void queue_free(queue *q) {
	queue_empty(q);
	free(q);
}

void *queue_peek(queue *q) {
	if (q->first == NULL) {
		return NULL;
	}
	return q->first->data;
}

void *queue_pop(queue *q) {
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

void queue_push(queue *q, void *data) {
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
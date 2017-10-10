/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "queue.h"

/**
 * Creates a new queue.
 *
 * @return the created queue
 */
queue *queue_create();

void queue_free(queue *q) {
	queue_item *cursor = q->first;
	queue_item *next = NULL;
	
	for (size_t i = 0; i < q->size; ++i) {
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	
	free(q);
}

/**
 * Gets the first item in the queue.
 *
 * @param q the queue
 * @return the first item in the queue
 */
void *queue_peek(queue *q);

/**
 * Pops the first item from the queue.
 *
 * @param q the queue
 * @return the first item in the queue, that has been removed
 */
void *queue_pop(queue *q);

/**
 * Pushes an item to the back of the queue.
 *
 * @param q the queue
 * @param item the item to push
 */
void queue_push(queue *q, void *item);
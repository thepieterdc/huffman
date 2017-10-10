/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_QUEUE_H
#define HUFFMAN_DATASTRUCTURES_QUEUE_H

#include <unistd.h>

/**
 * An item in the queue.
 */
typedef struct queue_item {
	struct queue_item *next;
	void *data;
} queue_item;

/**
 * A queue.
 */
typedef struct {
	struct queue_item *first;
	struct queue_item *last;
	size_t size;
} queue;

/**
 * Creates a new queue.
 *
 * @return the created queue
 */
queue *queue_create();

/**
 * Frees all memory allocated by the queue.
 *
 * @param q the queue
 */
void queue_free(queue *q);

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
 * @param data the data to push
 */
void queue_push(queue *q, void *data);

#endif /* HUFFMAN_DATASTRUCTURES_QUEUE_H */
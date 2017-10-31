/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_DATASTRUCTURES_BYTEQUEUE_H
#define HUFFMAN_DATASTRUCTURES_BYTEQUEUE_H

#include <unistd.h>
#include "../datatypes/bit.h"

/**
 * An item in the queue.
 */
typedef struct byte_queue_item {
	struct byte_queue_item *next;
	byte data;
} byte_queue_item;

/**
 * A queue for bytes.
 */
typedef struct byte_queue {
	struct queue_item *first;
	struct queue_item *last;
	size_t size;
} byte_queue;

/**
 * Creates a new byte queue.
 *
 * @return the created byte queue
 */
byte_queue *byte_queue_create();

/**
 * Removes all items from the byte queue.
 *
 * @param q the byte queue
 */
void byte_queue_empty(byte_queue *q);

/**
 * Frees all memory allocated by the byte queue.
 *
 * @param q the byte queue
 */
void byte_queue_free(byte_queue *q);

/**
 * Gets the first item in the byte queue.
 *
 * @param q the byte queue
 * @return the first item in the byte queue
 */
void *byte_queue_peek(byte_queue *q);

/**
 * Pops the first item from the byte queue.
 *
 * @param q the byte queue
 * @return the first item in the byte queue, that has been removed
 */
void *byte_queue_pop(byte_queue *q);

/**
 * Pushes an item to the back of the byte queue.
 *
 * @param q the byte queue
 * @param data the data to push
 */
void byte_queue_push(byte_queue *q, byte data);

#endif /* HUFFMAN_DATASTRUCTURES_BYTEQUEUE_H */
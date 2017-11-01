/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"
#include "test_datastructure_bytequeue.h"
#include "../src/datastructures/byte_queue.h"
#include "../src/util/string.h"

char *test_byte_queue_create_free() {
	byte_queue *q = byte_queue_create();
	assertNotNull(q);
	byte_queue_free(q);
	return 0;
}

char *test_byte_queue_empty() {
	byte_queue *q = byte_queue_create();
	assertNotNull(q);
	
	byte_queue_push(q, 5);
	byte_queue_push(q, 4);
	byte_queue_push(q, 3);
	byte_queue_push(q, 2);
	byte_queue_push(q, 1);
	assertEquals(q->size, 5);
	
	byte_queue_empty(q);
	assertEquals(q->size, 0);
	
	byte_queue_free(q);
	
	return 0;
}

char *test_byte_queue_push_peek_pop() {
	byte_queue *q = byte_queue_create();
	assertNotNull(q);
	
	byte_queue_push(q, 50);
	byte_queue_push(q, 60);
	byte_queue_push(q, 70);
	assertEquals(q->size, 3);
	
	assertTrue(byte_queue_pop(q) == 50);
	assertEquals(q->size, 2);

	assertTrue(byte_queue_peek(q) == 60);
	assertEquals(q->size, 2);
	
	byte_queue_free(q);
	
	return 0;
}
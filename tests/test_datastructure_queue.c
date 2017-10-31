/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"
#include "test_datastructure_queue.h"
#include "../src/datastructures/byte_queue.h"
#include "../src/util/string.h"

char *test_queue_create_free() {
	byte_queue *q = queue_create();
	assertNotNull(q);
	queue_free(q);
	return 0;
}

char *test_queue_empty() {
	byte_queue *q = queue_create();
	assertNotNull(q);
	
	queue_push(q, (void *) 5);
	queue_push(q, (void *) 4);
	queue_push(q, (void *) 3);
	queue_push(q, (void *) 2);
	queue_push(q, (void *) 1);
	assertEquals(q->size, 5);
	
	queue_empty(q);
	assertEquals(q->size, 0);
	
	queue_free(q);
	
	return 0;
}

char *test_queue_push_peek_pop() {
	byte_queue *q = queue_create();
	assertNotNull(q);
	
	queue_push(q, (void *) "fifty");
	queue_push(q, (void *) "sixty");
	queue_push(q, (void *) "seventy");
	assertEquals(q->size, 3);
	
	char *fifty = (char *) queue_pop(q);
	assertTrue(str_equals(fifty, "fifty"));
	assertEquals(q->size, 2);
	
	char *sixty = (char *) queue_peek(q);
	assertTrue(str_equals(sixty, "sixty"));
	assertEquals(q->size, 2);
	
	queue_free(q);
	
	return 0;
}
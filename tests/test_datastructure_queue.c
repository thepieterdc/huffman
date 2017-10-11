/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_unit.h"
#include "test_datastructure_queue.h"
#include "../src/datastructures/queue.h"
#include "../src/util/string.h"

char *test_queue_create_free() {
	queue *q = queue_create();
	assertThat(q != NULL);
	queue_free(q);
	return 0;
}

char *test_queue_empty() {
	queue *q = queue_create();
	assertThat(q != NULL);
	
	queue_push(q, (void *) 5);
	queue_push(q, (void *) 4);
	queue_push(q, (void *) 3);
	queue_push(q, (void *) 2);
	queue_push(q, (void *) 1);
	assertThat(q->size == 5);
	
	queue_empty(q);
	assertThat(q->size == 0);
	
	queue_free(q);
	
	return 0;
}

char *test_queue_push_peek_pop() {
	queue *q = queue_create();
	assertThat(q != NULL);
	
	queue_push(q, (void *) "fifty");
	queue_push(q, (void *) "sixty");
	queue_push(q, (void *) "seventy");
	assertThat(q->size == 3);
	
	char *fifty = (char *) queue_pop(q);
	assertThat(str_equals(fifty, "fifty"));
	assertThat(q->size == 2);
	
	char *sixty = (char *) queue_peek(q);
	assertThat(str_equals(sixty, "sixty"));
	assertThat(q->size == 2);
	
	queue_free(q);
	
	return 0;
}
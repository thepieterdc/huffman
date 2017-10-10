/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "linked_list.h"
#include "../util/errors.h"
#include "../util/logging.h"

/**
 * Adds an item to the linked list.
 *
 * @param ll the linked list
 * @param item the item to add
 */
void ll_add(linked_list *ll, void *item) {

}

linked_list *ll_create() {
	linked_list *ret = (linked_list*) malloc(sizeof(linked_list));
	if(!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->size = 0;
		ret->first = ret->last = NULL;
	}
	return ret;
}

void ll_free(linked_list *ll) {
	linked_list_item *cursor = ll->first;
	linked_list_item *next = NULL;
	while(cursor != NULL) {
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	free(ll);
}

void *ll_get(linked_list *ll, size_t idx) {
	return NULL;
}

void *ll_remove_index(linked_list *ll, size_t idx) {
	return NULL;
}
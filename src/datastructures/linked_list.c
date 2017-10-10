/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "linked_list.h"
#include "../util/errors.h"
#include "../util/logging.h"

linked_list *ll_create() {
	linked_list *ret = (linked_list*) malloc(sizeof(linked_list));
	if(!ret) {
		error(ERROR_MALLOC_FAILED);
	} else {
		ret->size = 0;
		ret->first = NULL;
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
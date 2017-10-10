/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_util_linked_list.h"
#include "../src/datastructures/linked_list.h"
#include "test_unit.h"

char *test_ll_add_get_remove() {
	linked_list *ll = ll_create();
	assertThat(ll != NULL);
	
	ll_add(ll, (void *) 'A');
	ll_add(ll, (void *) 'B');
	ll_add(ll, (void *) 'C');
	assertThat(ll->size == 3);
	
	char middle = (char) ll_get(ll, 1);
	assertThat(middle == 'B');
	assertThat(ll->size == 3);
	
	char last = (char) ll_remove_index(ll, 2);
	assertThat(last == 'C');
	assertThat(ll->size == 2);
	
	ll_free(ll);
}

char *test_ll_create_free() {
	linked_list *ll = ll_create();
	assertThat(ll != NULL);
	ll_free(ll);
	return 0;
}
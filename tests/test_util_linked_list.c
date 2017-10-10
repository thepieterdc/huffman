/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "test_util_linked_list.h"
#include "../src/datastructures/linked_list.h"
#include "test_unit.h"

char *test_ll_create_free() {
	linked_list *ll = ll_create();
	assertThat(ll != NULL);
	ll_free(ll);
	return 0;
}
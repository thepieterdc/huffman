/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */


#ifndef HUFFMAN_DATASTRUCTURES_LINKED_LIST_H
#define HUFFMAN_DATASTRUCTURES_LINKED_LIST_H

#include <unistd.h>

/**
 * An item in the linked list.
 */
typedef struct linked_list_item {
	struct linked_list_item *next;
	void *data;
} linked_list_item;

/**
 * A linked list.
 */
typedef struct {
	size_t size;
	struct linked_list_item *first;
} linked_list;

/**
 * Creates a new linked list.
 *
 * @return the created list
 */
linked_list *ll_create();

/**
 * Frees all memory allocated by the linked list.
 *
 * @param ll the linked list
 */
void ll_free(linked_list *ll);

#endif /* HUFFMAN_DATASTRUCTURES_LINKED_LIST_H */
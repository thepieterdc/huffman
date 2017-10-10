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
	struct linked_list_item *first;
	struct linked_list_item *last;
	size_t size;
} linked_list;

/**
 * Adds an item to the linked list.
 *
 * @param ll the linked list
 * @param item the item to add
 */
void ll_add(linked_list *ll, void *item);

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

/**
 * Gets the item at index idx of the linked list.
 *
 * @param ll the linked list
 * @param idx the index to get
 * @return the item at index idx of the list
 */
void *ll_get(linked_list *ll, size_t idx);

/**
 * Removes the item at index idx of the linked list.
 *
 * @param ll the linked list
 * @param idx the index to remove
 * @return the removed item at index idx of the list
 */
void *ll_remove_index(linked_list *ll, size_t idx);

#endif /* HUFFMAN_DATASTRUCTURES_LINKED_LIST_H */
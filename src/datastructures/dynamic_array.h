/***************************************************************
dynamic_array.h -- Data structure: dynamic array.
Copyright (c) 2016, BrainDeadDev.
All rights reserved.

Array that automatically expands when needed. Capacity only limited by available RAM.
Initial implementation 17.10.16, Tobiah Lissens
***************************************************************/

#ifndef PIESCAPE_PUBSUB_DYNAMIC_ARRAY_H
#define PIESCAPE_PUBSUB_DYNAMIC_ARRAY_H

typedef struct {
	size_t size;
	size_t max_size;
	void **array;
} dynamic_array;

/**
 * Creates a dynamic array.
 *
 * @return pointer to the dynamic_array
 */
dynamic_array *da_create();

/**
 * Initializes a dynamic array.
 *
 * @param da the array to initialize
 */
void da_init(dynamic_array *da);

/**
 * Adds an element to a dynamic array.
 *
 * @param da   the array that should be added to
 * @param item the item that should be added
 */
void da_add(dynamic_array *da, void *item);

/**
 * Adds an item to a dynamic array at a specified index.
 * <b>If the index contains an item, it will be overwritten.</b>
 *
 * @param da    the dynamic array to which the item should be added
 * @param index the index where the item should be added, should be < size
 * @param item  the itemthat should be added
 */
void da_add_index(dynamic_array *list, size_t index, void *item);

/**
 * Gets an item at a given index from a dynamic array.
 *
 * @param da    the da to search in
 * @param index the index to get
 * @return void the item at the given index
 */
void *da_get(dynamic_array *da, size_t index);

/**
 * Removes all instances of an item from a dynamic array.
 *
 * @param da   the dynamic array where the item should be removed
 * @param item the item that should be removed
 */
void da_remove_all_item_instances(dynamic_array *da, void *item);

/**
 * Removes the first occurrence of an item from a dynamic array.
 *
 * @param da   the dynamic array where the item should be removed
 * @param item the item that should be removed
 */
void da_remove_first_item_instance(dynamic_array *da, void *item);

/**
 * Removes the item at a given index from a dynamic array.
 *
 * @param da    the dynamic array where the item should be removed
 * @param index the item that should be removed
 */
void da_remove_index(dynamic_array *da, size_t index);

/**
 * Frees the memory allocated by a dynamic array.
 *
 * @param da the dynamic array to be freed
 */
void da_free(dynamic_array *da);

/**
 * Frees the memory allocated by the elements in a dynamic array.
 *
 * @param da the dynamic array to be freed
 */
void da_free_stack(dynamic_array *da);

/**
 * Expands the size of a dynamic array by factor 2.
 *
 * @param da the array to expand in size
 */
void da_dynamic_expand(dynamic_array *da);

#endif /* PIESCAPE_PUBSUB_DYNAMIC_ARRAY_H */
/***************************************************************
dynamic_array.c -- Data structure: dynamic array.
Copyright (c) 2016, BrainDeadDev.
All rights reserved.

Array that automatically expands when needed. Capacity only limited by available RAM.
Initial implementation 17.10.16, Tobiah Lissens
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "../util/errors.h"
#include "../util/logging.h"

#define DA_DEFAULT_SIZE (10)

dynamic_array *da_create() {
	dynamic_array *array = (dynamic_array *) malloc(sizeof(dynamic_array));
	if (!array) {
		error(ERROR_MALLOC_FAILED);
	}
	da_init(array);
	return array;
}

void da_init(dynamic_array *da) {
	da->max_size = DA_DEFAULT_SIZE;
	da->size = 0;
	da->array = malloc(sizeof(void *) * DA_DEFAULT_SIZE);
	if (!da->array) {
		error(ERROR_MALLOC_FAILED);
	}
	
}

void da_add(dynamic_array *da, void *item) {
	if (da->size == da->max_size) {
		da_dynamic_expand(da);
	}
	da->array[da->size] = item;
	da->size++;
}

void da_add_index(dynamic_array *da, size_t index, void *item){
	if (index >= da->size || index < 0){
		error(ERROR_INDEX_OUT_OF_BOUNDS);
	}
	da->array[index] = item;
}

void *da_get(dynamic_array *da, size_t index) {
	if (index >= da->size || index < 0) {
		error(ERROR_INDEX_OUT_OF_BOUNDS);
	}
	return da->array[index];
}

void da_remove_all_item_instances(dynamic_array *da, void *item) {
	size_t move = 0;
	for (size_t i = 0; i < da->size; ++i) {
		if (da->array[i] == item) {
			move++;
		} else {
			da->array[i - move] = da->array[i];
		}
	}
	da->size -= move;
}

void da_remove_first_item_instance(dynamic_array *da, void *item) {
	for (size_t i = 0; i < da->size; ++i) {
		if (da->array[i] == item) {
			da_remove_index(da, i);
			return;
		}
	}
}

void da_remove_index(dynamic_array *da, size_t index) {
	if (index >= da->size) {
		error(ERROR_INDEX_OUT_OF_BOUNDS);
	}
	for (size_t i = index; i < da->size - 1; ++i) {
		da->array[i] = da->array[i + 1];
	}
	da->array[da->size - 1] = NULL;
	da->size--;
}

void da_free(dynamic_array *da) {
	da_free_stack(da);
	free(da);
}

void da_free_stack(dynamic_array *da) {
	free(da->array);
}

void da_dynamic_expand(dynamic_array *da) {
	da->max_size *= 2;
	da->array = realloc(da->array, sizeof(void *) * da->max_size);
	if (!da->array) {
		error(ERROR_MALLOC_FAILED);
	}
}
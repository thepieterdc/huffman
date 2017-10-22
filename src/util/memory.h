/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#ifndef HUFFMAN_UTIL_MEMORY_H
#define HUFFMAN_UTIL_MEMORY_H

#include <unistd.h>

/**
 * Allocates and clears {amount} blocks of memory and generates an error upon failure.
 *
 * @param amount the amount of blocks to allocate
 * @param size the size of each block
 * @return the amount of memory to allocate
 */
void *callocate(size_t amount, size_t size);

/**
 * Allocates a block of memory and generates an error upon failure.
 *
 * @param size the amount of memory to allocate
 * @return the amount of memory to allocate
 */
void *mallocate(size_t size);

#endif /* HUFFMAN_UTIL_MEMORY_H */
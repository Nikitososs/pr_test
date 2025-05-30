#include "pool_allocator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Pool_allocator *pool_init(size_t block_size, size_t block_count) {
  Pool_allocator *pool_allocator = malloc(sizeof(Pool_allocator));
  pool_allocator->block_size = block_size;
  pool_allocator->block_count = block_count;

  size_t real_block_size = sizeof(Block) + block_size;
  size_t pool_volume = real_block_size * block_count;

  pool_allocator->data = malloc(pool_volume);

  if (pool_allocator->data == NULL) {
    free(pool_allocator);
    return NULL;
  }

  pool_allocator->freeList = NULL;

  for (size_t i = 0; i < block_count; i++) {
    void *curr_block = pool_allocator->data + i * real_block_size;
    Block *block = (Block *)curr_block;
    block->next = pool_allocator->freeList;
    pool_allocator->freeList = block;
  }

  return pool_allocator;
}

void *pool_alloc(Pool_allocator *pool_allocator) {
  if (pool_allocator->freeList == NULL) {
    return NULL;
  }

  Block *block = pool_allocator->freeList;
  pool_allocator->freeList = block->next;

  return (void *)((void *)block + sizeof(Block));
}

void pool_free(Pool_allocator *pool_allocator, void *ptr) {
  Block *block = (Block *)((void *)ptr - sizeof(Block));
  block->next = pool_allocator->freeList;
  pool_allocator->freeList = block;
}

void pool_dest(Pool_allocator *pool_allocator) {
  if (pool_allocator == NULL) {
    return;
  }
  free(pool_allocator->data);
  free(pool_allocator);
}

#include "pool_aloc.h"
#include <stdlib.h>

pool_allocator *pool_allocator_create(size_t block_size, size_t count) {
  pool_allocator *allocator = malloc(sizeof(pool_allocator));
  allocator->block_size = block_size;
  allocator->count = count;
  allocator->free_list = NULL;
  allocator->all = (pool_block *)malloc(block_size * count);
  for (size_t i = 0; i < count; i++) {
    pool_block *block = (pool_block *)((char *)allocator->all + i * block_size);
    block->next = allocator->free_list;
    allocator->free_list = block;
  }
  return allocator;
}
void *pool_allocator_alloc(pool_allocator *allocator) {
  if (!allocator->free_list)
    return NULL;

  pool_block *bl = allocator->free_list;
  allocator->free_list = bl->next;
  return (void *)bl;
}
void pool_allocator_free(pool_allocator *allocator, void *mem) {
  if (!mem)
    return;
  pool_block *bl = (pool_block *)mem;
  bl->next = allocator->free_list;
  allocator->free_list = bl;
}
void pool_allocator_destroy(pool_allocator *allocator) {
  if (!allocator)
    return;
  free(allocator->all);
  free(allocator);
}

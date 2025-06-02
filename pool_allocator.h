#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
  struct Block *next;
} Block;

typedef struct {
  Block *freeList;
  size_t block_size;
  size_t block_count;
  void *data;
} Pool_allocator;

Pool_allocator *pool_init(size_t block_size, size_t block_count);

void *pool_alloc(Pool_allocator *pool_allocator);

void pool_free(Pool_allocator *pool_allocator, void *ptr);

void pool_dest(Pool_allocator *pool_allocator);

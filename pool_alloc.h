#include <stddef.h>

typedef struct pool_block {
  struct pool_block *next;
} pool_block;

typedef struct {
  size_t block_size;
  size_t count;
  pool_block *free_list;
  pool_block *all;
} pool_allocator;

pool_allocator *pool_allocator_create(size_t block_size, size_t count);
void *pool_allocator_alloc(pool_allocator *allocator);
void pool_allocator_free(pool_allocator *allocator, void *mem);
void pool_allocator_destroy(pool_allocator *allocator);

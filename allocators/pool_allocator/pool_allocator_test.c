#include "pool_allocator.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test_pool_init() {
  size_t block_size = 64;
  size_t block_count = 8;
  Pool_allocator *pool = pool_init(block_size, block_count);
  assert(pool->block_count = block_count);
  assert(pool->block_size = block_size);
  assert(pool->freeList != NULL);
  pool_dest(pool);
}

void test_pool_alloc() {
  size_t block_size = 16;
  size_t block_count = 4;
  Pool_allocator *pool = pool_init(block_size, block_count);

  Block *first_block = pool_alloc(pool);
  Block *second_block = pool_alloc(pool);
  Block *third_block = pool_alloc(pool);
  Block *fourth_block = pool_alloc(pool);
  Block *fifth_block = pool_alloc(pool);
  assert(first_block != NULL && second_block != NULL && third_block != NULL &&
         fourth_block != NULL && fifth_block == NULL);
  pool_dest(pool);
}

void test_pool_free() {
  size_t block_size = 16;
  size_t block_count = 4;
  Pool_allocator *pool = pool_init(block_size, block_count);

  Block *first_block = pool_alloc(pool);
  Block *second_block = pool_alloc(pool);
  pool_free(pool, second_block);
  Block *third_block = pool_alloc(pool);
  pool_free(pool, second_block);
  Block *fourth_block = pool_alloc(pool);

  assert(third_block == second_block && fourth_block == second_block);
}

void test_pool_data() {
  size_t block_size = sizeof(int);
  size_t block_count = 2;
  Pool_allocator *pool = pool_init(block_size, block_count);

  int *first_number = (int *)pool_alloc(pool);
  int *second_number = (int *)pool_alloc(pool);

  *first_number = 777;
  *second_number = 999;

  assert(*first_number == 777 && *second_number == 999);
}

int main() {
  test_pool_init();
  test_pool_alloc();
  test_pool_free();
  test_pool_data();
  return 0;
}

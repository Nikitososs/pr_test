#include "linear_allocator.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void test_linear_init() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);
  assert(allocator.data != NULL);
  assert(allocator.volume == volume);
  assert(allocator.size == 0);
  linear_free(&allocator);
}

void test_linear_alloc() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  void *mem_block1 = linear_alloc(&allocator, 100);
  assert(mem_block1 != NULL);
  assert(allocator.size == 100);

  void *mem_block2 = linear_alloc(&allocator, 200);
  assert(mem_block2 != NULL);
  assert(allocator.size == 300);

  void *mem_block3 = linear_alloc(&allocator, 725);
  assert(mem_block3 == NULL);

  linear_free(&allocator);
}

void test_linear_reset() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  linear_alloc(&allocator, 300);
  assert(allocator.size == 300);

  linear_reset(&allocator);
  assert(allocator.size == 0);

  void *mem_block = linear_alloc(&allocator, 100);
  assert(mem_block == allocator.data);

  linear_free(&allocator);
}

void test_linear_free() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  linear_alloc(&allocator, 100);
  linear_free(&allocator);
  assert(allocator.volume == 0);
  assert(allocator.size == 0);
}

int main() {
  test_linear_init;
  test_linear_alloc();
  test_linear_reset();
  test_linear_free();
  return 0;
}
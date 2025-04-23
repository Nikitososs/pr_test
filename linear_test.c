#include "linear.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test1() {
  size_t size = sizeof(int) * 3;
  LinearAllocator *allocator = linear_allocator_create(size);
  int *arr1 = linear_allocator_alloc(allocator, 2 * sizeof(int));
  int *arr2 = linear_allocator_alloc(allocator, 2 * sizeof(int));
  arr1[0] = 10;
  arr1[1] = 3;
  assert(arr1[0] == 10 && arr1[1] == 3 && arr2 == NULL);
  linear_allocator_destroy(allocator);
}
void test2() {
  size_t size = sizeof(int) * 2;
  LinearAllocator *allocator = linear_allocator_create(size);
  int *arr1 = linear_allocator_alloc(allocator, 2 * sizeof(int));
  arr1[0] = 10;
  linear_allocator_reset(allocator);
  int *arr2 = linear_allocator_alloc(allocator, 2 * sizeof(int));
  arr2[0] = 3;
  assert(arr1[0] == 3 && arr2[0] == 3);
  linear_allocator_destroy(allocator);
}
void test3() {
  size_t size = 2 * sizeof(int);
  LinearAllocator *allocator = linear_allocator_create(size);
  assert(allocator != NULL);
  linear_allocator_destroy(allocator);
  int *arr1 = linear_allocator_alloc(allocator, 2 * sizeof(int));
  assert(arr1 == NULL);
}
int main() {
  test1();
  test2();
  test3();
  return 0;
}

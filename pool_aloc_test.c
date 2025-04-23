#include "pool_aloc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
void test1() {
  pool_allocator *allocator = pool_allocator_create(2 * sizeof(int), 1);
  int *arr1 = pool_allocator_alloc(allocator);
  arr1[0] = 2;
  arr1[1] = 4;
  int *arr2 = pool_allocator_alloc(allocator);
  assert(arr1[0] == 2 && arr1[1] == 4 && arr2 == NULL);
  pool_allocator_destroy(allocator);
}
void test2() {
  pool_allocator *allocator = pool_allocator_create(2 * sizeof(int), 2);
  int *arr1 = pool_allocator_alloc(allocator);
  arr1[0] = 2;
  arr1[1] = 4;
  assert(arr1[0] == 2 && arr1[1] == 4);
  pool_allocator_free(allocator, arr1);
  assert(arr1[0] != 2 && arr1[1] != 4);
  pool_allocator_destroy(allocator);
}
void test3() {
  pool_allocator *allocator = pool_allocator_create(2 * sizeof(int), 2);
  int *arr1 = pool_allocator_alloc(allocator);
  arr1[0] = 3;
  int *arr2 = pool_allocator_alloc(allocator);
  arr2[1] = 1;
  pool_allocator_destroy(allocator);
  assert(arr1[0] != 3 && arr2[1] != 1);
}
int main() {
  test1();
  test2();
  test3();
  return 0;
}

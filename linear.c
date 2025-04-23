#include "linear.h"
#include <stdlib.h>

LinearAllocator *linear_allocator_create(size_t size) {
  LinearAllocator *allocator = malloc(sizeof(LinearAllocator));
  allocator->buff = malloc(size);
  allocator->offset = 0;
  allocator->size = size;
  return allocator;
}

void *linear_allocator_alloc(LinearAllocator *allocator, size_t size) {
  if (allocator->offset + size > allocator->size)
    return NULL;
  void *res = allocator->buff + allocator->offset;
  allocator->offset += size;
  return res;
}
void linear_allocator_reset(LinearAllocator *allocator) {
  allocator->offset = 0;
}
void linear_allocator_destroy(LinearAllocator *allocator) {
  free(allocator->buff);
  free(allocator);
}

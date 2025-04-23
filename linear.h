#include <stddef.h>

typedef struct {
  void *buff;
  size_t offset;
  size_t size;
} LinearAllocator;

LinearAllocator *linear_allocator_create(size_t size);
void *linear_allocator_alloc(LinearAllocator *allocator, size_t size);
void linear_allocator_reset(LinearAllocator *allocator);
void linear_allocator_destroy(LinearAllocator *allocator);

#include <stddef.h>
#include <stdint.h>

typedef struct {
  size_t volume;
  size_t size;
  void *data;
} Linear_allocator;

Linear_allocator linear_init(size_t volume);

void *linear_alloc(Linear_allocator *linear_allocator, size_t size);

void linear_reset(Linear_allocator *linear_allocator);

void linear_free(Linear_allocator *linear_allocator);
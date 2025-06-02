#include "linear_allocator.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Linear_allocator linear_init(size_t volume) {
  void *data = malloc(volume);
  Linear_allocator linear_allocator = {
      .volume = volume,
      .size = 0,
      .data = data,
  };
  return linear_allocator;
}

void *linear_alloc(Linear_allocator *linear_allocator, size_t size) {
  if (linear_allocator->size + size > linear_allocator->volume) {
    return NULL;
  }
  void *ptr = linear_allocator->data + linear_allocator->size;
  linear_allocator->size += size;
  return ptr;
}

void linear_reset(Linear_allocator *linear_allocator) {
  linear_allocator->size = 0;
}

void linear_free(Linear_allocator *linear_allocator) {
  linear_allocator->volume = 0;
  linear_allocator->size = 0;
  free(linear_allocator->data);
}

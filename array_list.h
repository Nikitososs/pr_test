#include "linear_allocator.h"
#include <stddef.h>

typedef struct {
  size_t volume_for_all;
  size_t count;
  Linear_allocator *allocator;
  void **data;
} ArrayList;

void arraylist_init(ArrayList *list, Linear_allocator *allocator);

void arraylist_extend(ArrayList *list, size_t new_volume);

void arraylist_add(ArrayList *list, void *data, size_t index);

void *arraylist_get(ArrayList *list, size_t index);

void arraylist_del(ArrayList *list, size_t index);

void arraylist_free(ArrayList *list);

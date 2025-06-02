#include "array_list.h"
#include <assert.h>
#include <string.h>

void arraylist_init(ArrayList *list, Linear_allocator *allocator) {
  if (list == NULL) {
    return;
  }
  list->allocator = allocator;
  list->volume_for_all = 1;
  list->count = 0;
  list->data =
      (void **)linear_alloc(allocator, sizeof(void *) * list->volume_for_all);
}

void arraylist_extend(ArrayList *list, size_t new_volume_for_all) {
  void **new_data = (void **)linear_alloc(list->allocator,
                                          sizeof(void *) * new_volume_for_all);
  memcpy(new_data, list->data, sizeof(void *) * list->count);
  list->data = new_data;
  list->volume_for_all = new_volume_for_all;
}

void arraylist_add(ArrayList *list, void *element, size_t index) {
  if (list == NULL || index > list->count) {
    return;
  }
  if (list->count >= list->volume_for_all) {
    arraylist_extend(list, list->volume_for_all * 2);
  }
  if (index < list->count) {
    memmove(&list->data[index + 1], &list->data[index],
            sizeof(void *) * (list->count - index));
  }
  list->data[index] = element;
  list->count++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (list == NULL || index >= list->count) {
    return NULL;
  }
  return list->data[index];
}

void arraylist_del(ArrayList *list, size_t index) {
  if (list == NULL || index > list->count) {
    return;
  }
  if (index < list->count - 1) {
    memmove(&list->data[index], &list->data[index + 1],
            sizeof(void *) * (list->count - index - 1));
  }
  list->count--;
}

void arraylist_free(ArrayList *list) {
  if (list && list->allocator) {
    linear_free(list->allocator);
    list->data = NULL;
    list->volume_for_all = 0;
    list->count = 0;
    list->allocator = NULL;
  }
}

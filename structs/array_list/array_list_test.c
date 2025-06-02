#include "array_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arraylist_init_test() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  ArrayList list;
  arraylist_init(&list, &allocator);

  assert(list.volume_for_all == 1);
  assert(list.count == 0);
  arraylist_free(&list);
}

void arraylist_add___arraylist_extend___arraylist_get_test() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int *a = malloc(sizeof(int));
  *a = 777;
  arraylist_add(&list, a, 0);
  assert(list.count == 1);
  assert(*((int *)arraylist_get(&list, 0)) == 777);
  assert(list.volume_for_all == 1);

  int *b = malloc(sizeof(int));
  *b = 888;
  arraylist_add(&list, b, 1);
  assert(list.count == 2);
  assert(*((int *)arraylist_get(&list, 1)) == 888);
  assert(list.volume_for_all == 2);

  int *c = malloc(sizeof(int));
  *c = 999;
  arraylist_add(&list, c, 0);
  assert(list.count == 3);
  assert(list.volume_for_all == 4);

  assert(*((int *)arraylist_get(&list, 0)) == 999);
  assert(*((int *)arraylist_get(&list, 1)) == 777);
  assert(*((int *)arraylist_get(&list, 2)) == 888);

  free(a);
  free(b);
  free(c);
  arraylist_free(&list);
}

void arraylist_del_test() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int *a = malloc(sizeof(int));
  *a = 777;
  arraylist_add(&list, a, 0);

  int *b = malloc(sizeof(int));
  *b = 888;
  arraylist_add(&list, b, 1);

  int *c = malloc(sizeof(int));
  *c = 999;
  arraylist_add(&list, c, 2);

  arraylist_del(&list, 0);
  assert(*((int *)arraylist_get(&list, 0)) == 888);

  arraylist_del(&list, 0);
  assert(*((int *)arraylist_get(&list, 0)) == 999);

  free(a);
  free(b);
  free(c);
  arraylist_free(&list);
}

void arraylist_free_test() {
  size_t volume = 1024;
  Linear_allocator allocator = linear_init(volume);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int *a = malloc(sizeof(int));
  *a = 777;
  arraylist_add(&list, a, list.count);

  assert(list.count == 1);
  assert(list.data != NULL);
  assert(list.allocator != NULL);

  arraylist_free(&list);

  assert(list.data == NULL);
  assert(list.volume_for_all == 0);
  assert(list.count == 0);
  assert(list.allocator == NULL);

  free(a);
}

int main() {
  arraylist_init_test();
  arraylist_add___arraylist_extend___arraylist_get_test();
  arraylist_del_test();
  arraylist_free_test();
  return 0;
}

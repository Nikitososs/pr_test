#include "allocators/linear_allocator.h"
#include "allocators/pool_allocator.h"
#include "hash_table.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void *pool_alloc_wrapper(void *head, size_t sz) { return pool_alloc(head); }

void linear_free_wrapper(void *head, void *ptr) {}

void insert_and_get_test() {
  hash_table_t table;
  int ret = hashtable_init(3, sizeof(int), NULL, &table);

  int v1 = 100, v2 = 200, v3 = 300;

  ret = hashtable_insert(&table, "key1", &v1);
  assert(ret == HT_OK);

  ret = hashtable_insert(&table, "key2", &v2);
  assert(ret == HT_OK);

  ret = hashtable_insert(&table, "key3", &v3);
  assert(ret == HT_OK);

  int *res;

  res = (int *)hashtable_get(&table, "key1");
  assert(res && *res == 100);

  res = (int *)hashtable_get(&table, "key2");
  assert(res && *res == 200);

  res = (int *)hashtable_get(&table, "key3");
  assert(res && *res == 300);

  res = (int *)hashtable_get(&table, "wrong_key");
  assert(res == NULL);

  hashtable_free(&table);
}

void overflow_and_update_test() {
  hash_table_t table;
  int ret = hashtable_init(2, sizeof(int), NULL, &table);

  int v1 = 100, v2 = 200, v3 = 300;

  ret = hashtable_insert(&table, "key1", &v1);
  assert(ret == HT_OK);

  ret = hashtable_insert(&table, "key2", &v2);
  assert(ret == HT_OK);

  ret = hashtable_insert(&table, "key3", &v3);
  assert(ret == HT_FULL);

  int v2_new = 250;
  ret = hashtable_insert(&table, "key2", &v2_new);
  assert(ret == HT_OK);
  int *res = (int *)hashtable_get(&table, "key2");
  assert(res && *res == 250);

  hashtable_free(&table);
}

void deletion_test() {
  hash_table_t table;
  int ret = hashtable_init(2, sizeof(int), NULL, &table);
  assert(ret == HT_OK);

  int v1 = 100, v2 = 200, v3 = 300;

  ret = hashtable_insert(&table, "key1", &v1);
  assert(ret == HT_OK);

  ret = hashtable_insert(&table, "key2", &v2);
  assert(ret == HT_OK);

  ret = hashtable_delete(&table, "key2");
  assert(ret == HT_OK);

  int *res = (int *)hashtable_get(&table, "key2");
  assert(res == NULL);

  ret = hashtable_delete(&table, "key2");
  assert(ret == HT_NOT_FOUND);

  hashtable_free(&table);
}

void test_invalid_inputs() {
  hash_table_t table;
  int ret = hashtable_init(0, sizeof(int), NULL, &table);
  assert(ret == HT_ALLOC_FAIL);

  ret = hashtable_insert(NULL, "key", NULL);
  assert(ret == HT_ALLOC_FAIL);

  ret = hashtable_insert(&table, NULL, NULL);
  assert(ret == HT_ALLOC_FAIL);

  ret = hashtable_insert(&table, "key", NULL);
  assert(ret == HT_ALLOC_FAIL);

  void *res = hashtable_get(NULL, "key");
  assert(res == NULL);

  res = hashtable_get(&table, NULL);
  assert(res == NULL);

  ret = hashtable_delete(NULL, "key");
  assert(ret == HT_ALLOC_FAIL);

  ret = hashtable_delete(&table, NULL);
  assert(ret == HT_ALLOC_FAIL);
}

void test_pool_allocator() {
  hash_table_t table;
  int max_key_len = 5;

  Pool_allocator *pool =
      pool_init(sizeof(ht_item) + sizeof(int) + max_key_len, 1);
  assert(pool != NULL);

  allocator_t pool_allocator = {.head = pool,
                                .alloc = pool_alloc_wrapper,
                                .free = (void (*)(void *, void *))pool_free};

  int ret = hashtable_init(1, sizeof(int), &pool_allocator, &table);
  assert(ret == HT_OK);

  int v = 777;
  ret = hashtable_insert(&table, "key1", &v);
  assert(ret == HT_OK);

  int *res = (int *)hashtable_get(&table, "key1");
  assert(res && *res == 777);

  ret = hashtable_delete(&table, "key1");
  assert(ret == HT_OK);

  hashtable_free(&table);

  pool_dest(pool);
}

void test_linear_allocator() {
  hash_table_t table;

  size_t volume = 41;
  Linear_allocator allocator = linear_init(volume);

  allocator_t linear_allocator = {.head = &allocator,
                                  .alloc =
                                      (void *(*)(void *, size_t))linear_alloc,
                                  .free = linear_free_wrapper};

  int ret = hashtable_init(1, sizeof(int), &linear_allocator, &table);
  assert(ret == HT_OK);

  int v = 42;
  ret = hashtable_insert(&table, "key1", &v);
  assert(ret == HT_OK);

  int *res = hashtable_get(&table, "key1");
  assert(res && *res == 42);

  ret = hashtable_delete(&table, "key1");
  assert(ret == HT_OK);

  hashtable_free(&table);
  linear_free(&allocator);
}

int main() {
  insert_and_get_test();
  overflow_and_update_test();
  deletion_test();
  test_invalid_inputs();
  test_pool_allocator();
  test_linear_allocator();
  return 0;
}

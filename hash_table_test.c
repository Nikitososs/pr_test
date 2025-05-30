#include "hash_table.h"
#include "pool_allocator.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  Pool_allocator *pool;
} PoolAllocatorWrapper;

static void *pool_alloc_wrapper(void *head, size_t sz) {
  (void)sz;
  PoolAllocatorWrapper *wrapper = (PoolAllocatorWrapper *)head;
  return pool_alloc(wrapper->pool);
}

static void pool_free_wrapper(void *head, void *ptr) {
  PoolAllocatorWrapper *wrapper = (PoolAllocatorWrapper *)head;
  pool_free(wrapper->pool, ptr);
}

static void insert_and_get_test() {
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

static void overflow_and_update_test() {
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

static void deletion_test() {
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

static void test_invalid_inputs() {
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

static void test_custom_allocator() {
  hash_table_t table;

  Pool_allocator *pool = pool_init(sizeof(ht_item), 10);
  assert(pool != NULL);

  PoolAllocatorWrapper wrapper = {pool};

  allocator_t custom_alloc = {
      .head = &wrapper, .alloc = pool_alloc_wrapper, .free = pool_free_wrapper};

  int ret = hashtable_init(5, sizeof(int), &custom_alloc, &table);
  assert(ret == HT_OK);

  int v = 777;
  ret = hashtable_insert(&table, "key", &v);
  assert(ret == HT_OK);

  int *res = (int *)hashtable_get(&table, "key");
  assert(res && *res == 777);

  ret = hashtable_delete(&table, "key");
  assert(ret == HT_OK);

  hashtable_free(&table);

  pool_dest(pool);
}

int main() {
  insert_and_get_test();
  overflow_and_update_test();
  deletion_test();
  test_invalid_inputs();
  test_custom_allocator();

  return 0;
}

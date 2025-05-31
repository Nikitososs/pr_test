#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

size_t hash_func(const char *key, size_t capacity) {
  size_t hash = 0;
  while (*key) {
    hash++;
    key++;
  }
  return hash % capacity;
}

static void *default_alloc(void *head, size_t size) {
  (void)head;
  return malloc(size);
}
static void default_free(void *head, void *ptr) {
  (void)head;
  free(ptr);
}

int hashtable_init(size_t capacity, size_t value_size, allocator_t *allocator,
                   hash_table_t *table) {
  if (!table || capacity == 0 || value_size == 0)
    return HT_ALLOC_FAIL;

  table->capacity = capacity;
  table->count = 0;
  table->value_size = value_size;

  if (allocator)
    table->allocator = *allocator;
  else {
    table->allocator.head = NULL;
    table->allocator.alloc = default_alloc;
    table->allocator.free = default_free;
  }

  table->items = calloc(capacity, sizeof(ht_item *));
  if (!table->items)
    return HT_ALLOC_FAIL;

  return HT_OK;
}

int hashtable_insert(hash_table_t *table, const char *key, const void *value) {
  if (!table || !key || !value)
    return HT_ALLOC_FAIL;

  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;

  while (steps < table->capacity) {
    ht_item *item = table->items[hash];

    if (!item || item->is_deleted) {
      void *block = table->allocator.alloc(table->allocator.head,
                                           sizeof(ht_item) + table->value_size);
      if (!block)
        return HT_ALLOC_FAIL;

      ht_item *new_item = (ht_item *)block;

      size_t key_len = strlen(key) + 1;
      char *key_copy = table->allocator.alloc(table->allocator.head, key_len);
      if (!key_copy) {
        table->allocator.free(table->allocator.head, block);
        return HT_ALLOC_FAIL;
      }
      memcpy(key_copy, key, key_len);

      new_item->key = key_copy;
      new_item->value = (char *)block + sizeof(ht_item);
      memcpy(new_item->value, value, table->value_size);
      new_item->is_occupied = 1;
      new_item->is_deleted = 0;

      table->items[hash] = new_item;
      table->count++;
      return HT_OK;
    } else if (!item->is_deleted && strcmp(item->key, key) == 0) {
      memcpy(item->value, value, table->value_size);
      return HT_OK;
    }

    hash = (hash + 1) % table->capacity;
    steps++;
  }

  return HT_FULL;
}

void *hashtable_get(hash_table_t *table, const char *key) {
  if (!table || !key)
    return NULL;

  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;

  while (steps < table->capacity) {
    ht_item *item = table->items[hash];

    if (item && item->is_occupied && !item->is_deleted &&
        strcmp(item->key, key) == 0) {
      return item->value;
    }

    if (!item)
      return NULL;

    hash = (hash + 1) % table->capacity;
    steps++;
  }

  return NULL;
}

int hashtable_delete(hash_table_t *table, const char *key) {
  if (!table || !key)
    return HT_ALLOC_FAIL;

  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;

  while (steps < table->capacity) {
    ht_item *item = table->items[hash];

    if (item && item->is_occupied && !item->is_deleted &&
        strcmp(item->key, key) == 0) {
      table->allocator.free(table->allocator.head, item->key);
      table->allocator.free(table->allocator.head, item);
      table->items[hash] = NULL;
      table->count--;
      return HT_OK;
    }

    if (!item)
      return HT_NOT_FOUND;

    hash = (hash + 1) % table->capacity;
    steps++;
  }

  return HT_NOT_FOUND;
}

void hashtable_free(hash_table_t *table) {
  if (!table)
    return;

  for (size_t i = 0; i < table->capacity; i++) {
    if (table->items[i]) {
      table->allocator.free(table->allocator.head, table->items[i]->key);
      table->allocator.free(table->allocator.head, table->items[i]);
    }
  }

  free(table->items);
  table->items = NULL;
  table->capacity = 0;
  table->count = 0;
}

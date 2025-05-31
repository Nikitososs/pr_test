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

int hashtable_init(size_t capacity, size_t value_size, allocator_t *allocator, hash_table_t *table) {
  if (!table || capacity == 0 || value_size == 0)
    return HT_ALLOC_FAIL;

  table->capacity = capacity;
  table->count = 0;
  table->value_size = value_size;

  if (allocator) {
    table->allocator = *allocator;
  } else {
    table->allocator.head = NULL;
    table->allocator.alloc = default_alloc;
    table->allocator.free = default_free;
  }

  table->items = malloc(capacity * sizeof(ht_item));
  if (!table->items)
    return HT_ALLOC_FAIL;

  for (size_t i = 0; i < capacity; i++) {
    table->items[i].key = NULL;
    table->items[i].value = NULL;
    table->items[i].is_occupied = 0;
    table->items[i].is_deleted = 0;
  }

  return HT_OK;
}

int hashtable_insert(hash_table_t *table, const char *key, const void *value) {
  if (!table || !key || !value)
    return HT_ALLOC_FAIL;

  size_t hash = hash_func(key, table->capacity);
  size_t steps = 0;

  while (steps < table->capacity) {
    ht_item *item = &table->items[hash];

    if (!item->is_occupied || item->is_deleted) {
      item->key = (char *)key;

      void *val_ptr = table->allocator.alloc(table->allocator.head, table->value_size);
      if (!val_ptr)
        return HT_ALLOC_FAIL;

      memcpy(val_ptr, value, table->value_size);

      item->value = val_ptr;
      item->is_occupied = 1;
      item->is_deleted = 0;

      table->count++;
      return HT_OK;
    } else if (item->is_occupied && !item->is_deleted && strcmp(item->key, key) == 0) {
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
    ht_item *item = &table->items[hash];

    if (item->is_occupied && !item->is_deleted && item->key && strcmp(item->key, key) == 0) {
      return item->value;
    }
    if (!item->is_occupied && !item->is_deleted) {
      return NULL;
    }

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
    ht_item *item = &table->items[hash];

    if (item->is_occupied && !item->is_deleted && item->key && strcmp(item->key, key) == 0) {
      if (item->value) {
        table->allocator.free(table->allocator.head, item->value);
        item->value = NULL;
      }

      item->key = NULL;
      item->is_deleted = 1;
      item->is_occupied = 0;

      table->count--;
      return HT_OK;
    }

    if (!item->is_occupied && !item->is_deleted) {
      return HT_NOT_FOUND;
    }

    hash = (hash + 1) % table->capacity;
    steps++;
  }

  return HT_NOT_FOUND;
}

void hashtable_free(hash_table_t *table) {
  if (!table)
    return;

  for (size_t i = 0; i < table->capacity; i++) {
    if (table->items[i].is_occupied && !table->items[i].is_deleted && table->items[i].value) {
      table->allocator.free(table->allocator.head, table->items[i].value);
      table->items[i].value = NULL;
    }
  }

  if (table->items) {
    free(table->items);
    table->items = NULL;
  }

  table->capacity = 0;
  table->count = 0;
  table->value_size = 0;
}
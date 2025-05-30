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
  if (!table || capacity == 0)
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

  table->items = (ht_item *)table->allocator.alloc(table->allocator.head,
                                                   capacity * sizeof(ht_item));
  if (!table->items)
    return HT_ALLOC_FAIL;

  memset(table->items, 0, capacity * sizeof(ht_item));
  return HT_OK;
}

int hashtable_insert(hash_table_t *table, const char *key, void *value) {
  if (!table || !key || !value)
    return HT_ALLOC_FAIL;

  size_t index = hash_func(key, table->capacity);
  ssize_t first_deleted_index = -1;

  for (size_t i = 0; i < table->capacity; i++) {
    size_t j = (index + i) % table->capacity;
    ht_item *item = &table->items[j];

    if (!item->is_occupied) {
      if (first_deleted_index != -1) {
        item = &table->items[first_deleted_index];
        j = first_deleted_index;
      }

      size_t key_len = strlen(key) + 1;
      size_t total_size = sizeof(ht_item) + key_len + table->value_size;

      void *mem = table->allocator.alloc(table->allocator.head, total_size);
      if (!mem)
        return HT_ALLOC_FAIL;

      ht_item *allocated_item = (ht_item *)mem;
      char *key_ptr = (char *)(allocated_item + 1);
      void *value_ptr = key_ptr + key_len;

      strcpy(key_ptr, key);
      memcpy(value_ptr, value, table->value_size);

      item->key = key_ptr;
      item->value = value_ptr;
      item->is_occupied = 1;
      item->is_deleted = 0;
      item->raw_ptr = mem;

      table->count++;
      return HT_OK;
    } else if (item->is_deleted && first_deleted_index == -1) {
      first_deleted_index = j;
    } else if (!item->is_deleted && strcmp(item->key, key) == 0) {
      memcpy(item->value, value, table->value_size);
      return HT_OK;
    }
  }

  return HT_FULL;
}

void *hashtable_get(hash_table_t *table, const char *key) {
  if (!table || !key)
    return NULL;

  size_t index = hash_func(key, table->capacity);

  for (size_t i = 0; i < table->capacity; i++) {
    size_t j = (index + i) % table->capacity;
    ht_item *item = &table->items[j];

    if (!item->is_occupied) {
      return NULL;
    }
    if (!item->is_deleted && strcmp(item->key, key) == 0) {
      return item->value;
    }
  }
  return NULL;
}

int hashtable_delete(hash_table_t *table, const char *key) {
  if (!table || !key)
    return HT_ALLOC_FAIL;

  size_t index = hash_func(key, table->capacity);

  for (size_t i = 0; i < table->capacity; i++) {
    size_t j = (index + i) % table->capacity;
    ht_item *item = &table->items[j];

    if (!item->is_occupied) {
      return HT_NOT_FOUND;
    }
    if (!item->is_deleted && strcmp(item->key, key) == 0) {
      item->is_deleted = 1;
      table->count--;

      if (item->raw_ptr) {
        table->allocator.free(table->allocator.head, item->raw_ptr);
        item->raw_ptr = NULL;
      }

      item->key = NULL;
      item->value = NULL;
      return HT_OK;
    }
  }
  return HT_NOT_FOUND;
}

void hashtable_free(hash_table_t *table) {
  if (!table || !table->items)
    return;

  for (size_t i = 0; i < table->capacity; i++) {
    ht_item *item = &table->items[i];
    if (item->is_occupied && item->raw_ptr) {
      table->allocator.free(table->allocator.head, item->raw_ptr);
      item->raw_ptr = NULL;
    }
  }

  table->allocator.free(table->allocator.head, table->items);
  table->items = NULL;
  table->count = 0;
  table->capacity = 0;
}

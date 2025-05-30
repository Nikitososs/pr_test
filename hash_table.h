#include <stdio.h>

#define HT_OK 0
#define HT_FULL -1
#define HT_NOT_FOUND -2
#define HT_ALLOC_FAIL -3

typedef struct {
  void *head;
  void *(*alloc)(void *head, size_t size);
  void (*free)(void *head, void *ptr);
} allocator_t;

typedef struct {
  char *key;
  void *value;
  int is_occupied;
  int is_deleted;
  void *raw_ptr;
} ht_item;

typedef struct {
  size_t capacity;
  size_t count;
  size_t value_size;
  allocator_t allocator;
  ht_item *items;
} hash_table_t;

size_t hash(const char *key, size_t capacity);
int hashtable_init(size_t capacity, size_t value_size, allocator_t *allocator,
                   hash_table_t *table);

int hashtable_insert(hash_table_t *table, const char *key, void *value);
void *hashtable_get(hash_table_t *table, const char *key);
int hashtable_delete(hash_table_t *table, const char *key);
void hashtable_free(hash_table_t *table);
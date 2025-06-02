#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct list *create_list(int value) {
  struct list *ls = (struct list *)malloc(sizeof(struct list));
  ls->val = value;
  return ls;
}

int length(struct list *ls) {
  if (ls == NULL)
    return 0;
  int i = 1;
  while (ls->next != NULL) {
    ls = ls->next;
    i += 1;
  }
  return i;
}

int add_to_end(struct list *ls, int value) {
  while (ls->next != NULL)
    ls = ls->next;
  struct list *new = (struct list *)malloc(sizeof(struct list));
  new->val = value;
  ls->next = new;
  return 0;
}

int add_in_start(struct list *ls, int value) {
  int next = ls->val;
  ls->val = value;
  while (ls->next != NULL) {
    ls = ls->next;
    next = ls->val;
    ls->val = next;
  }
  ls->next = (struct list *)malloc(sizeof(struct list));
  ls->next->val = next;
  return 0;
}

int add_after_index(struct list *ls, int index, int value) {
  if (index < 0)
    return 0;
  int i = 0;
  while (ls->next != NULL && i < index) {
    ls = ls->next;
    i += 1;
  }
  struct list *next = ls->next;
  ls->next = (struct list *)malloc(sizeof(struct list));
  ls->next->val = value;
  ls->next->next = next;
  return 0;
}

int find_by_index(struct list *ls, int index) {
  if (index < 0)
    return 0;
  int i = 0;
  while (ls->next != NULL && i < index) {
    ls = ls->next;
    i += 1;
  }
  return ls->val;
}
int remove_by_index(struct list *ls, int index) {
  if (index < 0)
    return 0;
  int i = 0;
  while (ls->next != NULL && i < index) {
    ls = ls->next;
    i += 1;
  }
  if (i == 0)
    ;
  *ls = *ls->next;
  return 1;
}
void destroy(struct list *ls) {
  while (ls->next != NULL) {
    struct list *prev = ls;
    ls = ls->next;
    free(prev);
  }
  free(ls);
}

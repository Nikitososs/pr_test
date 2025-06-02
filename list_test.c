#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void add_to_end_test() {
  struct list *ls = create_list(5);
  add_to_end(ls, 3);
  assert(ls->next->val == 3);
  destroy(ls);
}
void length_test() {
  struct list *ls = create_list(5);
  add_to_end(ls, 3);
  assert(length(ls) == 2);
  assert(length(NULL) == 0);
  destroy(ls);
}
void add_in_start_test() {
  struct list *ls = create_list(5);
  add_in_start(ls, 12);
  assert(ls->val == 12 && ls->next->val == 5);
  destroy(ls);
}
void add_after_index_test() {
  struct list *ls = create_list(5);
  add_in_start(ls, 12);
  add_after_index(ls, 1, 4);
  assert(ls->val == 12 && ls->next->val == 5 && ls->next->next->val == 4);
  add_after_index(ls, 0, 11);
  assert(ls->next->val == 11);
  destroy(ls);
}
void find_by_index_test() {
  struct list *ls = create_list(5);
  add_in_start(ls, 3);
  assert(find_by_index(ls, 1) == 5 && find_by_index(ls, -1) == 0);
  destroy(ls);
}
void remove_by_index_test() {
  struct list *ls = create_list(5);
  add_in_start(ls, 3);
  assert(remove_by_index(ls, 0) == 1);
  assert(ls->val == 5 && remove_by_index(ls, -3) == 0);
  destroy(ls);
}
void destroy_test() {
  struct list *ls = create_list(5);
  add_in_start(ls, 3);
  assert(find_by_index(ls, 0) == 3);
  destroy(ls);
  assert(find_by_index(ls, 0) != 3);
}

int main() {
  add_to_end_test();
  length_test();
  add_in_start_test();
  add_after_index_test();
  find_by_index_test();
  remove_by_index_test();
  destroy_test();
  return 0;
}

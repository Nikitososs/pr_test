#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void push_test() {
  Stack st = stack();
  push(&st, 777);
  push(&st, 123);
  assert(contain(&st) == 1);
  free(st.data);
}

void pop_test() {
  Stack st = stack();
  push(&st, 777);
  push(&st, 123);
  assert(pop(&st) == 123);
  assert(pop(&st) == 777);
  assert(contain(&st) == 0);
  free(st.data);
}

void empty_pop_test() {
  Stack st = stack();
  assert(pop(&st) == 0);
  free(st.data);
}

void contain_test() {
  Stack st = stack();
  assert(contain(&st) == 0);
  push(&st, 3);
  assert(contain(&st) == 1);
  free(st.data);
}

int main() {
  push_test();
  pop_test();
  empty_pop_test();
  contain_test();
  return 0;
}

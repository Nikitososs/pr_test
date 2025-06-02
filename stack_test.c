#include "stack.h"
#include <assert.h>
#include <stdio.h>

void push_test() {
  int *st = stack();
  push(st, 777);
  push(st, 123);
  assert(contain(st) == 1);
}

void pop_test() {
  int *st = stack();
  push(st, 777);
  push(st, 123);
  assert(pop(st) == 123 && pop(st) == 777 && contain(st) == 0);
}

void empty_pop_test() {
  int *st = stack();
  assert(pop(st) == 0);
}

void contain_test() {
  int *st = stack();
  assert(contain(st) == 0);
  push(st, 3);
  assert(contain(st) == 1);
}

int main() {
  push_test();
  pop_test();
  empty_pop_test();
  contain_test();
  return 0;
}

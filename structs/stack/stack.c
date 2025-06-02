#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack stack() {
  Stack stack ={
    .size = 0,
    .data = NULL,
    .top = 0
  };
  return stack;
}

int push(Stack *stack, int value) {
    stack->size += 1;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
    stack->data[stack->top] = value;
    stack->top += 1;
    return 0;
}

int contain(Stack *stack) {
  return stack->top > 0;
}

int pop(Stack *stack) {
    if (stack->top == 0) return 0;
    stack->top -= 1;
    int value = stack->data[stack->top];
    stack->size -= 1;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
    return value;
}

void stack_free(Stack *stack) {
  free(stack->data);
  free(stack);
  stack = NULL;
}
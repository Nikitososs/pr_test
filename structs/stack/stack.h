typedef struct Stack {
  int *data;
  int size;
  int top;
} Stack;

#define NOT_IN_STACK = -1
#define IN_STACK = 0

Stack stack();
int push(Stack *stack, int value);
int pop(Stack *stack);
int contain(Stack *stack);
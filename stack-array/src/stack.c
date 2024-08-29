#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

typedef struct {
  size_t stack_size;
  size_t array_size;
  int *values;
} stack;

// Creates a new empty stack on the heap
stack *create_stack() {
  stack *new = (stack *)malloc(sizeof(stack));

  if (new == NULL) {
    printf("Unable to allocate memory");
    exit(1);
  }

  new->array_size = ARRAY_SIZE;
  new->stack_size = 0;
  new->values = (int *)calloc(ARRAY_SIZE, sizeof(int));

  if (new->values == NULL) {
    printf("Unable to allocate memory");
    free(new);
    exit(1);
  }

  return new;
}

// Destroys the stack, and frees up its memory
void destroy_stack(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  free(stk->values);
  free(stk);
}

// Adds the value val to the top of the stack
void push(stack *stk, int val) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }

  if (stk->stack_size == stk->array_size) {
    size_t new_size = stk->array_size * 2;
    int *values = (int *)realloc(stk->values, new_size * sizeof(int));
    if (values == NULL) {
      printf("Unable to allocate memory");
      return;
    }
    stk->array_size = new_size;
    stk->values = values;
  }

  stk->values[stk->stack_size++] = val;
}

// Removes and returns the topmost item of the stack
int pop(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return INT_MIN;
  }
  if (stk->stack_size < 1) {
    printf("Pop attempt on an empty stack");
    return INT_MIN;
  }
  return stk->values[--stk->stack_size];
}

// Returns the topmost item of the stack, without changing the stack
int peek_top(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return INT_MIN;
  }
  if (stk->stack_size < 1) {
    printf("Peek attempt on an empty stack");
    return INT_MIN;
  }
  return stk->values[stk->stack_size - 1];
}

// Returns the number of items on the stack
size_t stack_size(stack *stk) { return stk->stack_size; }

// Removes all of the items from the stack
void clear_stack(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  stk->stack_size = 0;
}

// Outputs the items in the stack to the console window
void print_stack(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  printf("[ ");
  for (size_t i = 0; i < stk->stack_size; i++) {
    printf("%d ", stk->values[i]);
  }
  printf("<-top ]\n");
}

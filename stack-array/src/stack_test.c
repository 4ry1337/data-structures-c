#include "stack.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void test_create_stack() {
  stack *stk = create_stack();
  assert(stk != NULL && stk->stack_size == 0 && stk->array_size == 10 &&
         stk->values != NULL);
  destroy_stack(stk);
  printf("Test create stack: Passed\n");
}

void test_destroy_stack() {
  stack *stk = create_stack();
  destroy_stack(stk);
  printf("Test destroy stack: Passed\n");
}

void test_print_stack() {
  stack *stk = create_stack();
  push(stk, 5);
  push(stk, 10);
  printf("Test print stack: Expected [ 5 10 <-top ]\n");
  printf("Actual: ");
  print_stack(stk);
  destroy_stack(stk);
}

void test_push() {
  stack *stk = create_stack();
  // Attempt to push 15 elements, with realloc
  for (size_t i = 0; i < 15; i++) {
    push(stk, i);
  }
  assert(stk->stack_size == 15 && stk->array_size == 20 &&
         stk->values[0] == 0 && stk->values[14] == 14 && stk->values != NULL);
  destroy_stack(stk);
  printf("Test push: Passed\n");
}

void test_pop() {
  stack *stk = create_stack();
  push(stk, 5);
  push(stk, 10);

  int value1 = pop(stk);
  int value2 = pop(stk);
  int value3 = pop(stk); // Attempting to pop from empty stack

  assert(value1 == 10 && value2 == 5 && value3 == INT_MIN &&
         stk->values != NULL);
  destroy_stack(stk);
  printf("Test pop: Passed\n");
}

void test_peek_top() {
  stack *stk = create_stack();
  push(stk, 5);
  push(stk, 10);

  int top1 = peek_top(stk);
  pop(stk);
  int top2 = peek_top(stk);
  pop(stk);
  int top3 = peek_top(stk); // Peek from empty stack

  assert(top1 == 10 && top2 == 5 && top3 == INT_MIN && stk->values != NULL);
  printf("Test peek top: Passed\n");
  destroy_stack(stk);
}

void test_clear_stack() {
  stack *stk = create_stack();
  // Attempt to push 15 elements, with realloc
  for (size_t i = 0; i < 15; i++) {
    push(stk, i);
  }
  clear_stack(stk);
  assert(stk->stack_size == 0 && stk->array_size == 20 && stk->values != NULL);
  destroy_stack(stk);

  printf("Test clear stack: Passed\n");
}

void test_stack_size() {
  stack *stk = create_stack();
  // Attempt to push 15 elements, with realloc
  for (size_t i = 0; i < 15; i++) {
    push(stk, i);
  }
  assert(stk->stack_size == stack_size(stk) && stk->values != NULL);
  destroy_stack(stk);

  printf("Test stack size: Passed\n");
}

/*
int main(int argc, char *argv[]) {
  test_create_stack();
  test_destroy_stack();
  test_stack_size();
  test_print_stack();
  test_push();
  test_pop();
  test_peek_top();
  return 0;
}
*/

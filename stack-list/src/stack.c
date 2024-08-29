#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

typedef struct _node {
  int value;
  struct _node *link;
} node;

typedef struct {
  size_t stack_size;
  node *top;
} stack;

void free_node(node *node) {
  if (node == NULL) {
    return;
  }
  free_node(node->link);
  free(node);
}

// Creates a new empty stack on the heap
stack *create_stack() {
  stack *stk = (stack *)malloc(sizeof(stack));
  stk->stack_size = 0;
  return stk;
}

// Destroys the stack, and frees up its memory
void destroy_stack(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  free_node(stk->top);
  free(stk);
}

// Adds the value val to the top of the stack
void push(stack *stk, int val) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  node *old_nodes = stk->top;
  node *new_node = (node *)malloc(sizeof(node));
  new_node->link = old_nodes;
  new_node->value = val;
  stk->top = new_node;
  stk->stack_size++;
}

// Removes and returns the topmost item of the stack
int pop(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return INT_MIN;
  }
  stk->stack_size--;
}

// Returns the topmost item of the stack, without changing the stack
int peek_top(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return INT_MIN;
  }
  return stk->top->value;
}

// Returns the number of items on the stack
size_t stack_size(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return INT_MIN;
  }
  int count = 0;
  node *temp;
  while (temp != NULL) {
    count++;
    temp = temp->link;
  }
  return count;
}

// Removes all of the items from the stack
void clear_stack(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  free_node(stk->top);
  // TODO: check this out
}

void print_node(node *node) {
  if (node == NULL) {
    return;
  }
  print_node(node->link);
  printf("%d ", node->value);
}

// Outputs the items in the stack to the console window
void print_stack(stack *stk) {
  if (stk == NULL) {
    printf("NULL stack pointer");
    return;
  }
  printf("[ ");
  print_node(stk->top);
  printf(" <-top ]");
}

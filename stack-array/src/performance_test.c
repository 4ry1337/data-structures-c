#include "stack.h"
#include <stdlib.h>

#include <stdio.h>
#include <sys/time.h>

int main() {
  struct timeval tv1, tv2;

  stack *stk = create_stack();

  gettimeofday(&tv1, NULL);

  for (int i = 0; i < 1000000 * 15 * 6; i++) {
    push(stk, i);
  }

  gettimeofday(&tv2, NULL);

  destroy_stack(stk);

  printf("Total time = %f seconds\n",
         (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
             (double)(tv2.tv_sec - tv1.tv_sec));
  return EXIT_SUCCESS;
}

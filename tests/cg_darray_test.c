/* Applies push and pop operations in a pseudorandom order, with varying
 * probability of each operation. Asserts that the popped values are
 * identical. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../code_gen.h"

CG_INIT(int, i)

/* For a  bias between 0 and 1, returns 1 with pseudo-probability = bias, and 0
 * otherwise */
int biased_toss(float bias) { return ((float)rand() / (RAND_MAX) < bias); }

void rand_test(void) {

  /* Initialises pseudo-random seed. */
  srand(time(NULL));
  int M = 10;
  int N = 20000000;

  for (int i = 1; i < M; i++) {
    int *ctrl_array = malloc(N * sizeof(int));
    int array_length = 0;
    i_darray *cg_darray = i_create(1);

    for (int j = 0; j < N; j++) {
      int index = rand() % array_length

                  if (biased_toss(((float)i) / ((float)M))) {}
      else {
      }
    }

    free(ctrl_array);
    i_destroy(cg_darray);

    printf("Successful test with %.1f push bias: ", ((float)i) / ((float)M));
    printf("%*d pushes, %*d pops\n", 8, pushes, 8, pops);
  }
}

int main(void) {
  rand_test();
  return 0;
}

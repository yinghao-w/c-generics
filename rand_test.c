/* Applies push and pop operations in a pseudorandom order, with varying
 * probability of each operation. Asserts that the popped values are
 * identical */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "code_gen.h"
#include "fat_pointer.h"

CG_INIT(int, i)

/* For a  bias between 0 and 1, returns 1 with pseudo-probability = bias, and 0
 * otherwise */
int biased_toss(float bias) {
	return ((float)rand() / (RAND_MAX) < bias); 
}

void rand_test(void) {

	/* Initialises pseudo-random seed. */
	srand(time(NULL));
	int M = 10;
	int N = 20000000;

	i_stack *cg_stack = i_create(1);
	int *fp_stack = NULL;

	for (int i = 1; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (biased_toss(((float) i) / ((float) M))) {
				i_push(j, cg_stack);
				fp_push(j, fp_stack);
			} else {
				assert(i_pop(cg_stack) == fp_pop(fp_stack));
			}
		}
		printf("Successful test with %.1f push bias.\n", ((float) i) / ((float) M));
	}
}

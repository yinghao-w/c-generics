/* Applies push and pop operations in a pseudorandom order, with varying
 * probability of each operation. Asserts that the popped values are
 * identical. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "code_gen.h"
#include "fat_pointer.h"
#include "void.h"

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

	for (int i = 1; i < M; i++) {
		i_stack *cg_stack = i_create(1);
		int *fp_stack = NULL;
		V_Stack *v_stack = v_create(1, sizeof(int));

		int pushes = 0;
		int pops = 0;

		for (int j = 0; j < N; j++) {
			if (biased_toss(((float) i) / ((float) M))) {
				i_push(j, cg_stack);
				fp_push(j, fp_stack);
				v_push(&j, v_stack);
				pushes++;
			} else {
				int p;
				v_pop(&p, v_stack);
				assert(p == i_pop(cg_stack));
				assert(p == fp_pop(fp_stack));
				pops++;
			}
		}

		i_destroy(cg_stack);
		fp_destroy(fp_stack);
		v_destroy(v_stack);
		printf("Successful test with %.1f push bias: ", ((float) i) / ((float) M));
		printf("%*d pushes, %*d pops\n", 8, pushes, 8, pops);
	}
}

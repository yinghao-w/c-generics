/* Stack speed test. Consists of 20 000 000 pushes of consecutive integers
 * or integral points, then pops each one. */

#include <time.h>
#include <stdio.h>

#include "code_gen.h"
#include "fat_pointer.h"
#include "r_void.h"

CG_INIT(int, i)

typedef struct point {
		int x;
		int y;
} point;
CG_INIT(point, pt)

void speed_test(void)
{
	int M = 10, N = 20000000, i, j;
	clock_t t;


	t = clock();
	for (i = 0; i < M; ++i) {
		i_stack *stack = i_create(2);
		for (j = 0; j < N; ++j)
			i_push(j, stack);
		for (j = 0; j < N; ++j)
			i_pop(stack);
		i_destroy(stack);
		
	}
	printf("code generation stack (int): %.3f sec\n",
		   (float)(clock() - t) / CLOCKS_PER_SEC);
	

	t = clock();
	for (i = 0; i < M; ++i) {
		pt_stack *stack = pt_create(2);
		for (j = 0; j < N; ++j)
			pt_push((point){j, j}, stack);
		for (j = 0; j < N; ++j)
			pt_pop(stack);
		pt_destroy(stack);
		
	}
	printf("code generation stack (point): %.3f sec\n",
		   (float)(clock() - t) / CLOCKS_PER_SEC);


	t = clock();
	for (i = 0; i < M; ++i) {
		int *stack = NULL;
		for (j = 0; j < N; ++j)
			fp_push(j, stack);
		for (j = 0; j < N; ++j)
			fp_pop(stack);
		fp_destroy(stack);
		
	}
	printf("fat pointer stack (int): %.3f sec\n",
		   (float)(clock() - t) / CLOCKS_PER_SEC);


	t = clock();
	for (i = 0; i < M; ++i) {
		point *stack = NULL;
		for (j = 0; j < N; ++j)
			fp_push(((point){j, j}), stack);
		for (j = 0; j < N; ++j)
			fp_pop(stack);
		fp_destroy(stack);
		
	}
	printf("fat pointer stack (point): %.3f sec\n",
		   (float)(clock() - t) / CLOCKS_PER_SEC);


	t = clock();
		for (i = 0; i < M; ++i) {
			/* TODO: better handling of no wanting output */
			char junk[sizeof(int)];
			V_Stack *stack = v_create(2, sizeof(int));
			for (j = 0; j < N; ++j)
				v_push(&j, stack);
			for (j = 0; j < N; ++j)
				v_pop(&junk, stack);
			v_destroy(stack);
			
		}
		printf("void * stack (int): %.3f sec\n",
			   (float)(clock() - t) / CLOCKS_PER_SEC);
	
	t = clock();
		for (i = 0; i < M; ++i) {
			/* TODO: better handling of no wanting output */
			char junk[sizeof(point)];
			point jj;
			V_Stack *stack = v_create(2, sizeof(point));
			for (j = 0; j < N; ++j) {
				jj = (point) {j, j};
				v_push(&jj, stack);	}
			for (j = 0; j < N; ++j)
				v_pop(&junk, stack);
			v_destroy(stack);
			
		}
		printf("void * stack (point): %.3f sec\n",
			   (float)(clock() - t) / CLOCKS_PER_SEC);
	
}

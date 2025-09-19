#include <time.h>
#include <stdio.h>
#include "code_gen.h"
/* #include \"void.h\" */
#include "fat_pointer.h"


CG_INIT(int, i)

typedef struct point {
		int x;
		int y;
} point;
CG_INIT(point, pt)


int main()
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


	/* t = clock(); */
	/* for (i = 0; i < M; ++i) { */
	/* 	Stack *stack = create(2); */
	/* 	for (j = 0; j < N; ++j) */
	/* 	{ */
	/* 		int *ele = malloc(sizeof(*ele)); */
	/* 		*ele = j; */
	/* 		push(ele, stack); */
	/* 	} */
	/* 	for (j = 0; j < N; ++j) */
	/* 		pop(stack); */
	/* 	destroy(stack); */
		
	/* } */
	/* printf(\"void stack (int): %.3f sec\n\", */
	/* 	   (float)(clock() - t) / CLOCKS_PER_SEC); */


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
	

	return 0;
}

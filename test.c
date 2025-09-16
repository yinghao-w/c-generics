#include <stdio.h>
#include <stdlib.h>
struct s {
	int a;
	void **b;
};

// p -> b -> *b -> **b=int
// 		b+1 -> *(b+1)


/*
 * 			darray ->
 * 						data -> *data -> **data = int
 * 						data+1->*(data+1)
 */

int main (void) {
	void *q = NULL;
	struct s *p = malloc(sizeof(*p));
	p->a = 7;
	p->b = malloc(2*sizeof(p->b));
	*p->b = malloc(sizeof(*p->b));
	*(p->b+1) = malloc(sizeof(*p->b));
	**(int **)(p->b) = 11;
	**(int **)(p->b+1) = 13;

	printf("%d\t%d\t%d\n", p->a, **(int **)p->b, **(int **)(p -> b+1));

	free(*(p->b));
	free(*(p->b+1));
	free((p->b));
	free(p);


	return 0;
}

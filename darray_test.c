#include <stdio.h>
#include <stdlib.h>
#include "void_darray.h"


int main(void) {

	Darray *test_darray = create(2);

	/* int *p[100]; */
	/* for (int i=0; i < 100; i++) { */
	/* 	p[i] = malloc(sizeof(p[i])); */ 
	/* 	*p[i] = 2*i; */
	/* 	append(p[i], test_darray); */
	/* } */

	int *q = malloc(sizeof(q));

	*q = 9999;

	for (int i=0; i<100; i++) {
		append(q, test_darray);
	}


	for (int i = 0; i < size(test_darray); i++) {
		printf("%d\n", *(int *)get(i, test_darray));
	}

	printf("%d\t%d\t%d\n", size(test_darray), is_in(q, test_darray), is_in(test_darray, test_darray));

	destroy(test_darray);

	return 0;
}

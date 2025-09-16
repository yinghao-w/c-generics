#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "void_darray.h"


int main(void) {

	Darray *test_darray = init(2);

	int *p[100];
	for (int i=0; i < 100; i++) {
		p[i] = malloc(sizeof(p[i])); 
		*p[i] = 2*i;
		append(p[i], test_darray);
	}


	for (int i = 0; i < size(test_darray); i++) {
		printf("%d\n", *(int *)get(i, test_darray));
	}
	destroy(test_darray);

	return 0;
}

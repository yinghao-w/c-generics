#include <assert.h>
#include <stdio.h>
#include "../code_gen.h"

CG_INIT(int, i)

void test(void) {
	i_darray *darray = i_create(1);
	i_push(1, darray);
	i_push(2, darray);
	i_delete(0, darray);
	i_insert(3, 1, darray);
	i_push(4, darray);
	i_insert(5, 0, darray);
	i_pop(darray);

	assert(i_length(darray) == 3);
	assert(i_get(0, darray) == 5);
	assert(i_get(1, darray) == 2);
	assert(i_get(2, darray) == 3);

	i_destroy(darray);
}

void test2(void) {
	i_darray *darray = i_create(1);
	for (int i = 0; i < 20; i++) {
		i_push(i, darray);
	}
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < i_length(darray); i++) {
			if (i_get(i, darray) % 2 == 0) {
				i_delete(i, darray);
				break;
			}	
		}
	}

	for (int i = 1; i < 10; i++) {
		i_insert(i * 100, 5, darray);
	}

	for (int i = 0; i < i_length(darray); i++) {
		printf("%d\n", i_get(i, darray));
	}	
}

int main(void) {
	test();
	test2();
	return 0;
}

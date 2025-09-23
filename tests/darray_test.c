#include <assert.h>
#include <stdio.h>
#include "../code_gen.h"
#include "../fat_pointer.h"
#include "../void.h"

CG_INIT(int, i)

void cg_test(void) {
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

void fp_test(void) {
	int *darray = NULL;
	fp_push(1, darray);
	fp_push(2, darray);
	fp_delete(0, darray);
	fp_insert(3, 1, darray);
	fp_push(4, darray);
	fp_insert(5, 0, darray);
	fp_pop(darray);

	assert(fp_length(darray) == 3);
	assert(darray[0] == 5);
	assert(darray[1] == 2);
	assert(darray[2] == 3);

	fp_destroy(darray);
}

void v_test(void) {
	V_Darray *darray = v_create(1, sizeof(int));
	int i = 1;
	v_push(&i, darray);
	i = 2;
	v_push(&i, darray);
	v_delete(&i, 0, darray);
	i = 3;
	v_insert(&i, 1, darray);
	i = 4;
	v_push(&i, darray);
	i = 5;
	v_insert(&i, 0, darray);
	v_pop(&i, darray);

	assert(v_length(darray) == 3);

	v_get(&i, 0, darray);
	assert(i = 5);
	v_get(&i, 1, darray);
	assert(i = 2);
	v_get(&i, 2, darray);
	assert(i = 3);

	v_destroy(darray);
}

void cg_test2(void) {
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

void fp_test2(void) {
	int *darray = NULL;
	for (int i = 0; i < 20; i++) {
		fp_push(i, darray);
	}
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < fp_length(darray); i++) {
			if (darray[i] % 2 == 0) {
				fp_delete(i, darray);
				break;
			}	
		}
	}

	for (int i = 1; i < 10; i++) {
		fp_insert(i * 100, 5, darray);
	}

	for (int i = 0; i < fp_length(darray); i++) {
		printf("%d\n", darray[i]);
	}	
}

int main(void) {
	cg_test();
	fp_test();
	v_test();
	cg_test2();
	printf("\n\n\n");
	fp_test2();
	return 0;
}

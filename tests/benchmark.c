/* Darray speed test. Consists of 20 000 000 pushes of consecutive integers
 * or integral points, then pops each one. */

#include <time.h>
#include <stdio.h>

#include "../../klib/kvec.h"

#define STB_DS_IMPLEMENTATION
#include "../../stb/stb_ds.h"

#define T vec_int, int, (c_use_cmp)
#include "../../STC/include/stc/vec.h"

void speed_test(void)
{
	int M = 10, N = 20000000, i, j;
	clock_t t;


	t = clock();
	for (i = 0; i < M; ++i) {
		kvec_t(int) darray;
		kv_init(darray);
		for (j = 0; j < N; ++j)
			kv_push(int, darray, j);
		for (j = 0; j < N; ++j)
			kv_pop(darray);
	kv_destroy(darray);
	}
	printf("KLIB KVEC: %.3f sec\n",
		   (float)(clock() - t) / CLOCKS_PER_SEC);


	t = clock();
	for (i = 0; i < M; ++i) {
		int* darray = NULL;
		for (j = 0; j < N; ++j)
			arrput(darray, j);
		for (j = 0; j < N; ++j)
			arrpop(darray);
		arrfree(darray);
	}
	printf("STB_DS: %.3f sec\n",
		   (float)(clock() - t) / CLOCKS_PER_SEC);


	}

int main(void) {
	speed_test();
	return 0;
}

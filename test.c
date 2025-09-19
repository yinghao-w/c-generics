#include <stdio.h>
#include "fat_pointer.h"

#define FUNC(x) 

int main(void) {

	int *a = NULL;
	int Q = 99999999;

	for (int i = 0; i<Q; i++) {
		fp_push(2 * i, a);
	};
	printf("%d\t%d\n", FP_HEADER(a) -> length, FP_HEADER(a) -> capacity);

	for (int i = 0; i<Q; i++) {
		fp_pop(a);
	};

	int A = 1;
	int B = FUNC(a);

	return 0;
}
 	

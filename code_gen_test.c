#include <stdio.h>
#include "code_gen.h"

INIT(int, i);

int main(void) {

	idarray *p = icreate(4);
	for (int i=0; i<4; i++) {
		p -> data[i] = 10 * i;
	};
	for (int i=0; i<4; i++) {
		printf("%d\n", p -> data[i]);
	};

	printf("");
	return 0;
}

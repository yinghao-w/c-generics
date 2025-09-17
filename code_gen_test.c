#include <stdio.h>
#include "code_gen.h"

struct point {
	int a;
	int b;
};
typedef struct point point;

void init_pt (point *pt, int a, int b) {
	pt -> a = a;
	pt -> b = b;
}

int comp_pt (point p, point q) {
	return (p == q);
}


INIT(point, pt)

int main(void) {

	point q;

	pt_darray *p = pt_create(4);
	for (int i=0; i<4; i++) {
		init_pt(p -> data+i, 3 *i, 7*i);
	};
	for (int i=0; i<4; i++) {
		printf("%d\n", p -> data[i].b);
	};

	printf("");
	return 0;
}

#include <stdio.h>

#define T_TYPE int
#define T_PREFIX it
#include "tree.h"

typedef struct {int x; int y;} point;

#define T_TYPE point
#define T_PREFIX Pt
#include "tree.h"

void testp(void) {
	Pt_Node *one = Pt_leaf((point){.x = 1, .y = 2});
	Pt_Node *two = Pt_leaf((point){.x = 5, .y = 4});
	Pt_Node *three = Pt_join((point){.x = 3, .y = 4}, one, two);
	foreach(Pt_Node, node, three) {
		printf("%d\n", node->value.x);
	}
}



void test(void) {
	it_Node *one = it_leaf(1);
	it_Node *two = it_leaf(2);
	it_Node *three = it_join(3, two, NULL);
	it_Node *four = it_join(4, one, three);
	it_Node *five = it_leaf(5);
	it_Node *six = it_join(6, NULL, five);
	it_Node *seven = it_join(7, four, six);
	foreach(it_Node, node, seven) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(it_Node, node, six) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(it_Node, node, three) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(it_Node, node, one) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	int i = 0;
	foreach(it_Node, node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	i = 0;
	foreach(it_Node, node, seven) {
		foreach(it_Node, mode, node) {
			i++;
		}	
	}
	printf("\t%d\n", i);
	it_destroy(seven);
}

int main(void) {
	test();
	testp();
	return 0;
}

#include <stdio.h>
#include <assert.h>
#include "../cg_bintree.h"

CG_BINTREE_INIT(int, Ibt)

struct pt {char x; char y;};

/* create the following tree:
 *     4
 *    /
 *   3
 *  / \
 * 1   2 */
void test(void) {
	Ibt_Bnode *one = Ibt_leaf(1);
	Ibt_Bnode *two = Ibt_leaf(2);
	Ibt_Bnode *three = Ibt_join(3, one, two);
	Ibt_Bnode *four = Ibt_join(4, three, NULL);

	assert(CG_IS_LEAF(one));
	assert(CG_IS_LEAF(two));
	assert(!CG_IS_LEAF(three));
	assert(!CG_IS_LEAF(four));

	assert(CG_NUM_CHILDREN(one) == 0);
	assert(CG_NUM_CHILDREN(three) == 2);
	assert(CG_NUM_CHILDREN(four) == 1);

	assert(three -> rchild == two);

	struct pt p = {.x = 'a', .y = 'b'};
	Ibt_Bnode *five = Ibt_leaf(p);
	assert(five);
}

int main(void) {
	test();
	return 0;
}

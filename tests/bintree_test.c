#include "../cg_bintree.h"
#include <assert.h>
#include <stdio.h>

CG_BINTREE_INIT(int, Ibt)

struct pt {
  char x;
  char y;
};

/* create the following tree:
 *     4
 *    /
 *   3
 *  / \
 * 1   2 */
void test(void) {
  Ibt_Node *one = Ibt_leaf(1);
  Ibt_Node *two = Ibt_leaf(2);
  Ibt_Node *three = Ibt_join(3, one, two);
  Ibt_Node *four = Ibt_join(4, three, NULL);

  assert(t_is_leaf(one));
  assert(t_is_leaf(two));
  assert(!t_is_leaf(three));
  assert(!t_is_leaf(four));

  assert(t_num_children(one) == 0);
  assert(t_num_children(three) == 2);
  assert(t_num_children(four) == 1);

  assert(three->rchild == two);

  Ibt_Node_darray *arr = Ibt_traverse(four);
  assert(Ibt_Node_get(0, arr)->value == 1);
  assert(Ibt_Node_get(1, arr)->value == 3);
  assert(Ibt_Node_get(2, arr)->value == 2);
  assert(Ibt_Node_get(3, arr)->value == 4);

  Ibt_destroy(four);
  Ibt_Node_destroy(arr);
}

int main(void) {
  test();
  return 0;
}

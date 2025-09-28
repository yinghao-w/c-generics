#include <assert.h>
#include <stdio.h>

#define T_TYPE int
#define T_PREFIX it
#include "../tree.h"

typedef struct {
  int x;
  int y;
} point;

#define T_TYPE point
#define T_PREFIX Pt
#include "../tree.h"

void test1(void) {
  it_Node *one = it_leaf(1);
  it_Node *two = it_leaf(2);
  it_Node *three = it_join(3, two, NULL);
  it_Node *four = it_join(4, one, three);
  it_Node *five = it_leaf(5);
  it_Node *six = it_join(6, NULL, five);
  it_Node *seven = it_join(7, four, six);

  /*	7---6---5
          |---4---3
                  |	|
                  1	2
  */

  assert(t_is_leaf(five));
  assert(!t_is_leaf(three));
  assert(t_is_root(seven));
  assert(!t_is_root(one));

  printf("%d\n", it_height(seven));

  int i = 0;
  foreach (it_Node, node, seven) {
    i++;
    assert(i == node->value);
  }
  i = 1;
  foreach (it_Node, node, three) {
    i++;
    assert(i == node->value);
  }
  i = 0;
  foreach (it_Node, node, one) {
    assert(1 == node->value);
  }
  foreach (it_Node, node1, seven) {
    foreach (it_Node, node2, node1) {
      i++;
    }
  }
  assert(i == 18);
  it_destroy(seven);
}

int ptcmp(point p, point q) { return (p.x == q.x) && (p.y == q.y); }

void test2(void) {
  Pt_Node *one = Pt_leaf((point){.x = 1, .y = 2});
  Pt_Node *two = Pt_join((point){.x = 3, .y = 2}, one, NULL);

  foreach (Pt_Node, node, two) {
    assert(node->rchild == NULL);
  }
  Pt_destroy(two);
}

int main(void) {
  test1();
  test2();
  return 0;
}

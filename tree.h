/* A generic implementation of binary trees using the "template-instantiation"
 * or "multiple inclusion" method. It was developed for use as an abstract
 * syntax tree, so there are no sorting or searching functions.
 *
 *
 * Use:
 *
 * Define prefix and type for the tree, and include this file:
 *
 * 		#define T_PREFIX i
 * 		#define T_TYPE int
 * 		#include "tree.h"
 *
 * Create a leaf node with a given value and no parents nor children:
 *
 * 		i_Node new_node = i_leaf(1);
 *
 * Create a node with two children:
 *
 * 		i_Node parent_node = i_join(5, left_child, right_child);
 *
 * Free a node and all its children:
 *
 * 		i_destroy(done_node);
 *
 * Iterate over all the nodes in a tree in post-order:
 *
 * 		for(i_Node, my_node, tree_root) {
 * 			do(my_node);
 * 		}
 *
 * 	The iterator does not require the current node pointer to find the
 * 	successor node; my_node may be modified or freed in each iteration. In fact
 * 	this is the implementation of the destructor.
 */

#include <stdio.h>
#ifdef T_PREFIX
#ifdef T_TYPE

#define T_CONCAT_2(A, B) A##_##B
#define T_CONCAT(A, B) T_CONCAT_2(A, B)

#define P_Node T_CONCAT(T_PREFIX, Node)

#include <stdlib.h>

typedef struct P_Node P_Node;
struct P_Node {
	T_TYPE value;
	P_Node *parent;
	P_Node *lchild;
	P_Node *rchild;
};

static P_Node *T_CONCAT(T_PREFIX, leaf)(T_TYPE value) {
	P_Node *p = malloc(sizeof(*p));
	p -> value = value;
	p -> parent = NULL;
	p -> lchild = NULL;
	p -> rchild = NULL;
	return p;
}

static P_Node *T_CONCAT(T_PREFIX, join)(T_TYPE value, P_Node *lchild, P_Node *rchild) {
	P_Node *p = malloc(sizeof(*p));
	p -> value = value;
	p -> parent = NULL;
	p -> lchild = lchild;
	p -> rchild = rchild;
	if (lchild != NULL) {
		lchild -> parent = p;
	}
	if (rchild != NULL) {
		rchild -> parent = p;
	}
	return p;
}

#define t_is_leaf(node) ((node->lchild == NULL) && (node->rchild == NULL))

#define t_is_root(node) ( node->parent == NULL)

#define t_num_children(node) ((node->lchild != NULL) + (node->rchild != NULL))

/* Detach node from its parent */
static void T_CONCAT(T_PREFIX, detach)(P_Node *node) {
	if (node->parent->lchild == node) {
		node->parent->lchild = NULL;
	} else if (node->parent->rchild == node) {
		node->parent->rchild = NULL;
	}
	node->parent = NULL;

}

#define t_shift(prev, curr, next, new_next) 	(*prev = *curr, *curr = *next, *next = new_next)

/* Returns 0 is *prev is to be visited now, 0 if it is to be skipped for later */
static int T_CONCAT(P_Node, single_traverse)(P_Node *root, P_Node **prev, P_Node **curr, P_Node **next) {
		if ((*curr == NULL) && (*next == NULL)) {
			*prev = NULL;
			return 0;

		} else if (*next == root->parent) {
			*prev = root;
			*curr = NULL;
			*next = NULL;
			return 0;

		} else if ((*next)->parent == *curr) {
			if ((*next)->lchild != NULL) {
				t_shift(prev, curr, next, (*next)->lchild);
			} else if ((*next)->rchild != NULL) {
				t_shift(prev, curr, next, (*next)->rchild);
			} else if (1) {
				t_shift(prev, curr, next, (*next)->parent);
			}

		} else if ((*next)->lchild == *curr) {
			if ((*next)->rchild != NULL) {
				t_shift(prev, curr, next, (*next)->rchild);
			} else if (1) {
				t_shift(prev, curr, next, (*next)->parent);
			}
			return 0;

		} else if (1) {
			t_shift(prev, curr, next, (*next)->parent);
			return 0;

		}
		return 1;
}

static void T_CONCAT(P_Node, traverse)(P_Node *root, P_Node **prev, P_Node **curr, P_Node **next) {
	int flag = 1;
	while (flag) {
		flag = T_CONCAT(P_Node, single_traverse)(root, prev, curr, next);
	}
}

static int T_CONCAT(P_Node, check)(P_Node *root, P_Node **prev, P_Node **curr, P_Node **next) {
	if ((*prev == NULL) && (*next) == root) {
		T_CONCAT(P_Node,traverse)(root, prev, curr, next);
	}
	return (*prev != NULL) || (*curr != NULL) || (*next != NULL);
}

static int T_CONCAT(T_PREFIX, height)(P_Node *root) {
	P_Node *prev = NULL;
	P_Node *curr = root->parent;
	P_Node *next = root;
	int i = 0;
	int max = 0;
	while (next != root->parent) {
		i += T_CONCAT(P_Node, single_traverse)(root, &prev, &curr, &next) ? 1 : -1;
		max = (i > max ? i : max);
	}
	return max - 1;
}

#define foreach(type, node, root)												\
	for(type *node = NULL, *node##curr = root->parent, *node##next = root;		\
		T_CONCAT(type, check)(root, &node, &node##curr, &node##next);						\
		T_CONCAT(type, traverse)(root, &node, &node##curr, &node##next))

static void T_CONCAT(T_PREFIX, destroy)(P_Node *root) {
	foreach(P_Node, node, root) {
		free(node);
	}
}

/* Compares if two trees have the same values. Takes a function pointer which
 * compares two T_TYPE values, returns 1 if the same, 0 if different. */
static int T_CONCAT(T_PREFIX, is_equal)(P_Node *root1, P_Node *root2, int (*val_is_equal)(T_TYPE, T_TYPE)) {
	/* if both nodes are null: */
	if (!root1 && !root2) {
		return 1;
	/* one of them is null */
	} else if (!root1 || !root2) {
		return 0;
	/* values differ */
	} else if (!(*val_is_equal)(root1->value, root2->value)) {
		return 0;
	} else {
		return T_CONCAT(T_PREFIX, is_equal)(root1->lchild, root2->lchild, val_is_equal) && T_CONCAT(T_PREFIX, is_equal)(root1->lchild, root2->lchild, val_is_equal)
	}

}

#undef T_TYPE
#undef T_PREFIX

#undef P_Node

#endif
#endif


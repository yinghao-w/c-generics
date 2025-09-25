#define T_TYPE int
#define T_PREFIX i

#ifdef T_TYPE
#ifdef T_PREFIX

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

P_Node *T_CONCAT(T_PREFIX, leaf)(T_TYPE value) {
	P_Node *p = malloc(sizeof(*p));
	p -> value = value;
	p -> parent = NULL;
	p -> lchild = NULL;
	p -> rchild = NULL;
	return p;
}

P_Node *T_CONCAT(T_PREFIX, join)(T_TYPE value, P_Node *lchild, P_Node *rchild) {
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

int t_is_leaf(P_Node *node) {
	return (node->lchild == NULL) && (node->rchild == NULL);
}

int t_is_root(P_Node *node) {
	return node->parent == NULL;
}

int t_num_children(P_Node *node) {
	return (node->lchild != NULL) + (node->rchild != NULL);
}

void t_disconnectn(P_Node *parent, int child) {
	if (child == 0) {
		parent->lchild->parent = NULL;
		parent ->lchild = NULL;
	} else if (child == 1) {
		parent->rchild->parent = NULL;
		parent ->rchild = NULL;
	}
}

void t_disconnectc(P_Node *parent, P_Node *child) {
	if (parent->lchild == child) {
		parent->lchild = NULL;
	} else if (parent->rchild == child) {
		parent->rchild = NULL;
	}
	child->parent = NULL;

}

#include <stdio.h>

void t_shift(P_Node **prev, P_Node **curr, P_Node **next, P_Node *new_next) {
	*prev = *curr;
	*curr = *next;
	*next = new_next;
}

void t_traverse(P_Node *root, P_Node **prev, P_Node **curr, P_Node **next) {
	while (1) {
		if ((*curr == NULL) && (*next == NULL)) {
			*prev = NULL;
			return;

		} else if (*next == root->parent) {
			*prev = root;
			*curr = NULL;
			*next = NULL;
			return;

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
			return;

		} else if (1) {
			t_shift(prev, curr, next, (*next)->parent);
			return;

		}
	}
}

int t_check(P_Node *root, P_Node **prev, P_Node **curr, P_Node **next) {
	if ((*prev == NULL) && (*next) == root) {
		t_traverse(root, prev, curr, next);
	}
	return (*prev != NULL) || (*curr != NULL) || (*next != NULL);
}

#define foreach(type, node, root)												\
	for(type *node = NULL, *node##curr = root->parent, *node##next = root;		\
			t_check(root, &node, &node##curr, &node##next);						\
			t_traverse(root, &node, &node##curr, &node##next))

//TODO: implement where instead of curr and next iterator metadata, use a cocnrete P_Node structure as the metadata
//can initialise for loop as: for(P_Node *node, meta;;), node will be P_Node * but meta will just be P_Node

void t_destroy(P_Node *root) {
	foreach(P_Node, node, root) {
		free(node);
	}
}
#undef T_TYPE
#undef T_PREFIX

#undef T_CONCAT_2
#undef T_CONCAT

#undef P_Node

#endif
#endif

void test(void) {
	i_Node *one = i_leaf(1);
	i_Node *two = i_leaf(2);
	i_Node *three = i_join(3, two, NULL);
	i_Node *four = i_join(4, one, three);
	i_Node *five = i_leaf(5);
	i_Node *six = i_join(6, NULL, five);
	i_Node *seven = i_join(7, four, six);
	foreach(i_Node, node, seven) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(i_Node, node, six) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(i_Node, node, three) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(i_Node, node, one) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	int i = 0;
	foreach(i_Node, node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	i = 0;
	foreach(i_Node, node, seven) {
		foreach(i_Node, mode, node) {
			i++;
		}	
	}
	printf("\t%d\n", i);
	t_destroy(seven);
}

//TODO: research finite state machine implementation of decision tree
//

int main(void) {
	test();
	return 0;
} 

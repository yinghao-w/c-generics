

#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
struct Node {
	int value;
	Node *parent;
	Node *lchild;
	Node *rchild;
};

Node *leaf(int value) {
	Node *p = malloc(sizeof(*p));
	p -> value = value;
	p -> parent = NULL;
	p -> lchild = NULL;
	p -> rchild = NULL;
	return p;
}

Node *join(int value, Node *lchild, Node *rchild) {
	Node *p = malloc(sizeof(*p));
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

int is_leaf(Node *node) {
	return (node->lchild == NULL) && (node->rchild == NULL);
}

int is_root(Node *node) {
	return node->parent == NULL;
}

int num_children(Node *node) {
	return (node->lchild != NULL) + (node->rchild != NULL);
}

void disconnectn(Node *parent, int child) {
	if (child == 0) {
		parent->lchild->parent = NULL;
		parent ->lchild = NULL;
	} else if (child == 1) {
		parent->rchild->parent = NULL;
		parent ->rchild = NULL;
	}
}

void disconnectc(Node *parent, Node *child) {
	if (parent->lchild == child) {
		parent->lchild = NULL;
	} else if (parent->rchild == child) {
		parent->rchild = NULL;
	}
	child->parent = NULL;

}

#include <stdio.h>

void shift(Node **prev, Node **curr, Node **next, Node *new_next) {
	*prev = *curr;
	*curr = *next;
	*next = new_next;
}

void traverse(Node *root, Node **prev, Node **curr, Node **next) {
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
				shift(prev, curr, next, (*next)->lchild);
			} else if ((*next)->rchild != NULL) {
				shift(prev, curr, next, (*next)->rchild);
			} else if (1) {
				shift(prev, curr, next, (*next)->parent);
			}

		} else if ((*next)->lchild == *curr) {
			if ((*next)->rchild != NULL) {
				shift(prev, curr, next, (*next)->rchild);
			} else if (1) {
				shift(prev, curr, next, (*next)->parent);
			}
			return;

		} else if (1) {
			shift(prev, curr, next, (*next)->parent);
			return;

		}
	}
}

int check(Node *root, Node **prev, Node **curr, Node **next) {
	if ((*prev == NULL) && (*next) == root) {
		traverse(root, prev, curr, next);
	}
	return (*prev != NULL) || (*curr != NULL) || (*next != NULL);
}

#define foreach(node, root)\
	for(Node *node = NULL, *node##curr = root->parent, *node##next = root; check(root, &node, &node##curr, &node##next); traverse(root, &node, &node##curr, &node##next))


void destroy(Node *root) {
	foreach(node, root) {
		free(node);
	}
}

void test(void) {
	Node *one = leaf(1);
	Node *two = leaf(2);
	Node *three = join(3, two, NULL);
	Node *four = join(4, one, three);
	Node *five = leaf(5);
	Node *six = join(6, NULL, five);
	Node *seven = join(7, four, six);
	foreach(node, seven) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(node, six) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(node, three) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach(node, one) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	int i = 0;
	foreach(node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	i = 0;
	foreach(node, seven) {
		foreach(mode, node) {
			i++;
		}	
	}
	printf("\t%d\n", i);
	destroy(seven);
}

//TODO: research finite state machine implementation of decision tree
//

int main(void) {
	test();
	return 0;
} 

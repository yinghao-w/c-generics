

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
/* Table
 *						 State: Previous decision:
 *					|		|up		|left	|right	|
 *					---------------------------------
 *					|up		|3		|2		|1		|
 *					---------------------------------
 *		 Possibility|left	|1		|		|		|
 * 					---------------------------------
 * 					|right	|2		|1		|		|
*/

#include <stdio.h>

int traverse1(Node *root, Node **curr, Node**next) {

	if ((*curr == root) && (*next == (*curr)->parent)) {
		return 0;
	}

	while (1) {

	Node *temp = *next;
	int exit = 0;

	if (*curr == (*next)->parent) {					// from up

		if ((*next)->lchild != NULL) {				// go left
			*next = (*next)->lchild;
		} else if ((*next)->rchild != NULL){		// go right
			*next = (*next)->rchild;
		} else if ((*next)->parent != NULL) {		// go up
			*next = (*next)->parent;
			exit = 1;
		}

	} else if (*curr == (*next)->lchild) {			// from left

		if ((*next)->rchild != NULL) {				// go right
			*next = (*next)->rchild;
		} else if ((*next)->rchild == NULL){		// go up
			*next = (*next)->parent;
			exit = 1;
		}

	} else if (*curr == (*next)->rchild) {			// from right

		*next = (*next)->parent;					// go up
		exit = 1;
	}
	*curr = temp;
	if (exit == 1) {break;}
	}
	return 1;
}

#define foreach1(node, root)\
	for(Node *node = root->parent, *node##next = root; traverse1(root, &node, &node##next);)

// traverse1 works, as does foreach, but not really for destroy. Problem is that the node after next can only be found with info from curr, which is freed. So the:
// 'next = curr->parent' check to end the loop does not work

void destroy1(Node *node) {
	foreach1(subnode, node) {
		free(subnode);
	}
}

void func1(void) {
	Node *one = leaf(1);
	Node *two = leaf(2);
	Node *three = join(3, two, NULL);
	Node *four = join(4, one, three);
	Node *five = leaf(5);
	Node *six = join(6, NULL, five);
	Node *seven = join(7, four, six);
	foreach1(node, seven) {
		printf("%d\n", node->value);
	}
	foreach1(node, six) {
		printf("%d\n", node->value);
	}
	foreach1(node, three) {
		printf("%d\n", node->value);
	}
	foreach1(node, one) {
		printf("%d\n", node->value);
	}
	int i = 0;
	foreach1(node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	destroy1(seven);
}

void shift(Node **prev, Node **curr, Node **next, Node *new_next) {
	*prev = *curr;
	*curr = *next;
	*next = new_next;
}

void traverse2(Node *root, Node **prev, Node **curr, Node **next) {


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

int end2(Node *root, Node **prev, Node **curr, Node **next) {
	if ((*prev == NULL) && (*next) == root) {
		traverse2(root, prev, curr, next);
	}
	return (*prev != NULL) || (*curr != NULL) || (*next != NULL);
}

Node *begin2p(Node *root) {
	Node *node = root;
	traverse2(root, &node, NULL, NULL);
	return node;
}

#define foreach2(node, root)\
	for(Node *node = NULL, *node##curr = root->parent, *node##next = root; end2(root, &node, &node##curr, &node##next); traverse2(root, &node, &node##curr, &node##next))

void destroy2(Node *root) {
	foreach2(node, root) {
		free(node);
	}
}

void func2(void) {
	Node *one = leaf(1);
	Node *two = leaf(2);
	Node *three = join(3, two, NULL);
	Node *four = join(4, one, three);
	Node *five = leaf(5);
	Node *six = join(6, NULL, five);
	Node *seven = join(7, four, six);
	foreach2(node, seven) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach2(node, six) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach2(node, three) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	foreach2(node, one) {
		printf("%d\n", node->value);
	}
	printf("\n\n");
	int i = 0;
	foreach2(node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	i = 0;
	foreach2(node, seven) {
		foreach2(mode, node) {
			i++;
		}	
	}
	printf("\t%d\n", i);
	destroy2(seven);
}

//TODO: research finite state machine implementation of decision tree
//
/*
 * int height(Node *node) {
 * 		int max = 0;
 * 		int i = 0;
 * 		foreachnodewithrepeatstraversal(subnode, node) {
 * 			i++ if went down
 * 			i-- if went up
 * 			max = max(max, i)
 * 		}
 * 		return max
 * } */

int main(void) {
	func2();
	return 0;
} 

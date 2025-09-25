

#include <stdlib.h>

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


int traverse(Node *root, Node **prev, Node **curr) {
	while(1) {
		if ((*curr == root) && (*prev == (*curr)->rchild)) {
			*prev = *curr;
			return 0;
		} else if (*curr == NULL) { //swap
			*curr = *prev;
			*prev = NULL;
		} else if (*prev == (*curr)->rchild) {
			*prev = *curr;
			*curr = (*curr)->parent;
		} else if (*prev == (*curr)->lchild) {
			*prev = *curr;
			*curr = (*curr)->rchild;
		} else if (*prev == (*curr)->parent) { //go left
			*prev = *curr;
			*curr = (*curr)->lchild;
		}
		if ((*curr != NULL) && (*prev == (*curr)->rchild)) {
			return 1;
		}
		if ((*prev == root) && (*curr == (*prev)->parent)) {
			return 1;
		}
	}
}

/* Node *begin(Node *root) { */
/* 	Node *curr = root->lchild; */
/* 	traverse(root, &root, &curr); */
/* 	return curr; */
/* } */

#define foreach(node, root)\
	for(Node *node = root->lchild, *node##prev=root; traverse(root, &node##prev, &node);)
	/* for(Node *node = begin(root), *node##prev=NULL; node != node##prev; traverse(root, &node##prev, &node)) */

// TODO: Use curr next instead of prev curr to simplify iterative destructor implementation
void destroy(Node *node) {
	foreach(subnode, node) {
		free(subnode);
	}
}
#include <stdio.h>
void func(void) {
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
	foreach(node, six) {
		printf("%d\n", node->value);
	}
	foreach(node, three) {
		printf("%d\n", node->value);
	}
	foreach(node, one) {
		printf("%d\n", node->value);
	}
	int i = 0;
	foreach(node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	i = 0;
	foreach(node, seven) {
		foreach(nnode, node) {
			i++;
		}
	}
	printf("\t%d\n", i);
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
	foreach(node, seven) {
		i++;
	}
	printf("\t%d\n", i);
	destroy1(seven);
}

//TODO: research finite state machine implementation of decision tree

int main(void) {
	func1();
	return 0;
}

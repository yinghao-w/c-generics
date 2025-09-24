#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int value;
	Node *parent;
	Node *lchild;
	Node *rchild;
};

/* I want this:
 * for (MACRO(node)) {
 * 		do(node);
 * }
 *
 * or:
 *
 * for (node = root; !iter_end(node); next(node)) {
 * 		do(node);
 * }
 *
 * or:
 *
 * for_each(node) {
 * 		do(node);
 * }
 */

int is_leaf(Node *node) {
	return (node->lchild == NULL) && (node->rchild == NULL);
}

int is_root(Node *node) {
	return node->parent == NULL;
}

int num_children(Node *node) {
	return (node->lchild != NULL) + (node->rchild != NULL);
}

Node *join(int value, Node *lchild, Node *rchild) {
	Node *p = malloc(sizeof(*p));
	p -> value = value;
	p -> parent = NULL;
	p -> lchild = lchild;
	p -> rchild = rchild;
	return p;
}

void traverse(Node **prev, Node **curr) {
	while(1) {
		if (*curr == NULL) { //swap
			Node *temp = *curr;
			*curr = *prev;
			*prev = temp;
		} else if (*prev == (*curr)->parent) { //go left
			*prev = *curr;
			*curr = (*curr)->lchild;
		} else if (*prev == (*curr)->lchild) { //go right
			*prev = *curr;
			*curr = (*curr)->rchild;
		} else { /* if (*prev == (*curr)->rchild) */
			*prev = *curr;
			*curr = (*curr)->parent;
		}
		if (*prev == (*curr)->rchild) {
			return;
		}
	}
}

Node *begin(Node *root) {
	traverse(&root->lchild, &root);
	return root;
}

Node *end(Node *root, Node *prev, Node *curr) {
	;
}

/* typedef Node Iterator; */
/* /1* Traverses the tree, can and will visit internal nodes thrice *1/ */
/* void traversE(Iterator *iter) { */
/* 	if (iter->prev == iter->curr->parent) { */
/* 		iter->prev = iter->curr; */
/* 		iter->curr = iter->curr->lchild; */
/* 	} else if (iter->prev == iter->curr->lchild) { */
/* 		iter->prev = iter->curr; */
/* 		iter->curr = iter->curr->rchild; */
/* 	} else { */
/* 		iter->prev = iter->curr; */
/* 		iter->curr = iter->curr->parent; */
/* 	} */
/* } */

/* /1* Iterates over the nodes in LRN order *1/ */
/* Node *nexT(Iterator *iter) { */
/* 	while(1) { */
/* 		traversE(iter); */
/* 		if (is_leaf(iter->curr)) { */
/* 			return iter->curr; */
/* 		} else if (iter->curr == iter->prev->parent) { */
/* 			return iter->curr; */
/* 		} */
/* 	} */
/* } */

/* int enD(Iterator *iter) { */
/* 	if (iter->curr->parent == NULL) { */
/* 		free(iter); */
/* 		return 1; */
/* 	} */
/* 	return 0; */
/* } */

/* #define fornode(node, root)\ */
/* 	Iterator node##iter = {.prev = root, .curr = root->lchild};\ */
/* 	for (Node *node = root->lchild; !enD(&node##iter); node = nexT(&node##iter)) */

/* #define fornode2(node, root)\ */
/* 	for(Node * node = root->child; prev = root; ##curr = root->lchild;) */
	
/* void func(void) { */
/* 	Node myroot = {1, NULL, NULL, NULL}; */
/* 	Node *p = &myroot; */

/* 	Iterator qter = {.prev = p, .curr = p->lchild}; */
/* 	for (Node *n = p -> lchild, ; !enD(&qter); n = nexT(&qter)) { */
/* 		free(n); */
/* 	} */

/* 	fornode(N, p) { */
/* 		free(N); */
/* 	} */
/* 	fornode(NN, p) { */
/* 		free(NN); */
/* 	} */
/* } */

/* void versE(curr, next) { */
/* 	for (int i = 2, float j = 3;;) { */
/* 		; */
/* 	} */
/* 	if (curr == next->parent) { */
/* 		curr = next; */
/* 		next = next->lchild; */
/* 	} else if (curr == next->lchild) { */
/* 		curr = next; */
/* 		next = next->rchild; */
/* 	} else { */
/* 		curr = next; */
/* 		next = next->parent; */
/* 	} */
/* } */

/* /1* // for (START; !end(root, node, ##next); traverse(node, ##next)) *1/ */


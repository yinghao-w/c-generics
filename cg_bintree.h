#ifndef CG_BINTREE_H

#define CG_BINTREE_H

#include <stdlib.h>

#define CG_BINTREE_INIT(TYPE, PREFIX)										\
	T_MAKE_NODE(TYPE, PREFIX)												\
	T_MAKE_LEAF(TYPE, PREFIX)												\
	T_MAKE_JOIN(TYPE, PREFIX)												\
	T_MAKE_DESTROY(TYPE, PREFIX)											\
	T_MAKE_TRAVERSE(TYPE, PREFIX)

#define T_MAKE_NODE(TYPE, PREFIX) 											\
	typedef struct PREFIX##_Node PREFIX##_Node;								\
	struct PREFIX##_Node {													\
		TYPE value;															\
		PREFIX##_Node *lchild;												\
		PREFIX##_Node *rchild;												\
	};

#define T_MAKE_LEAF(TYPE, PREFIX) 											\
	PREFIX##_Node *PREFIX##_leaf(TYPE value) {								\
		PREFIX##_Node *p = malloc(sizeof(*p));								\
		p -> value = value;													\
		p -> lchild = NULL;													\
		p -> rchild = NULL;													\
		return p;\
	}

#define T_MAKE_JOIN(TYPE, PREFIX) 											\
	PREFIX##_Node *PREFIX##_join(TYPE value, PREFIX##_Node *lchild, PREFIX##_Node *rchild) {\
		PREFIX##_Node *p = malloc(sizeof(*p));								\
		p -> value = value;													\
		p -> lchild = lchild;												\
		p -> rchild = rchild;												\
		return p;															\
	}

/* recursive implementation TODO: implement iterative */
#define T_MAKE_DESTROY(TYPE, PREFIX) 										\
	void PREFIX##_destroy(PREFIX##_Node *node) {							\
		if (node == NULL) {													\
			return;															\
		}																	\
		PREFIX##_destroy(node -> lchild);									\
		PREFIX##_destroy(node -> rchild);									\
		free(node);															\
	}

#define t_is_leaf(node)														\
	(((node->lchild == NULL) && (node->rchild == NULL)) ? 1 : 0)

#define t_num_children(node) 												\
	((node -> lchild != NULL) + (node -> rchild != NULL))

#include "code_gen.h"

#define T_MAKE_TRAVERSE(TYPE, PREFIX)										\
	CG_INIT(PREFIX##_Node *, PREFIX##_Node)									\
	/* In order traversal */												\
	static PREFIX##_Node##_darray *PREFIX##_traverse(PREFIX##_Node *node) {	\
		if (node == NULL) {													\
			return NULL;													\
		}																	\
		PREFIX##_Node##_darray *stack = PREFIX##_Node##_create(1);			\
		PREFIX##_Node##_darray *out = PREFIX##_Node##_create(1);			\
		while ((PREFIX##_Node##_length(stack) > 0) || (node != NULL)) {		\
			if (node != NULL) {												\
				PREFIX##_Node##_push(node, stack);							\
				node = node->lchild;										\
			} else {														\
				node = PREFIX##_Node##_pop(stack);							\
				PREFIX##_Node##_push(node, out);							\
				node = node->rchild;										\
			}																\
		}																	\
		PREFIX##_Node##_destroy(stack);										\
		return out;															\
	}


#endif

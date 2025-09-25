#ifndef CG_BINTREE_H

#define CG_BINTREE_H

#include <stdlib.h>

#define CG_BINTREE_INIT(TYPE, PREFIX)										\
	T_MAKE_NODE(TYPE, PREFIX)												\
	T_MAKE_LEAF(TYPE, PREFIX)												\
	T_MAKE_JOIN(TYPE, PREFIX)												\
	T_MAKE_DESTROY(TYPE, PREFIX)											\

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

#endif

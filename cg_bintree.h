#ifndef CG_BINTREE_H

#define CG_BINTREE_H

#include <stdlib.h>

#define CG_BINTREE_INIT(TYPE, PREFIX)										\
	MAKE_BNODE(TYPE, PREFIX)												\
	MAKE_LEAF(TYPE, PREFIX)													\
	MAKE_JOIN(TYPE, PREFIX)													\
	MAKE_DESTROY(TYPE, PREFIX)												\

#define MAKE_BNODE(TYPE, PREFIX) 											\
	typedef struct PREFIX##_Bnode PREFIX##_Bnode;							\
	struct PREFIX##_Bnode {													\
		TYPE value;															\
		PREFIX##_Bnode *lchild;												\
		PREFIX##_Bnode *rchild;												\
	};

#define MAKE_LEAF(TYPE, PREFIX) 											\
	PREFIX##_Bnode *PREFIX##_leaf(TYPE value) {								\
		PREFIX##_Bnode *p = malloc(sizeof(*p));								\
		p -> value = value;													\
		p -> lchild = NULL;													\
		p -> rchild = NULL;													\
		return p;\
	}

#define MAKE_JOIN(TYPE, PREFIX) 											\
	PREFIX##_Bnode *PREFIX##_join(TYPE value, PREFIX##_Bnode *lchild, PREFIX##_Bnode *rchild) {\
		PREFIX##_Bnode *p = malloc(sizeof(*p));								\
		p -> value = value;													\
		p -> lchild = lchild;												\
		p -> rchild = rchild;												\
		return p;															\
	}

/* recursive implementation TODO: implement iterative */
#define MAKE_DESTROY(TYPE, PREFIX) 											\
	void PREFIX##_destroy(PREFIX##_Bnode *bnode) {							\
		if (bnode == NULL) {												\
			return;															\
		}																	\
		PREFIX##_destroy(bnode -> lchild);									\
		PREFIX##_destroy(bnode -> rchild);									\
		free(bnode);														\
	}

#define CG_IS_LEAF(bnode)													\
	(((bnode->lchild == NULL) && (bnode->rchild == NULL)) ? 1 : 0)

#define CG_NUM_CHILDREN(bnode) 												\
	(																		\
	(bnode -> lchild == NULL) ?												\
	(bnode -> rchild == NULL ? 0 : 1) :										\
	(bnode -> rchild == NULL ? 1 : 2)										\
	)

#endif

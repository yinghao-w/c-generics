#ifndef CG_BINTREE_H

#define CG_BINTREE_H

#define CG_BINTREE_INIT(TYPE, PREFIX)					\
	MAKE_BNODE(TYPE, PREFIX)\
	MAKE_CREATE(TYPE, PREFIX)\
	MAKE_DESTROY(TYPE, PREFIX)\

#define MAKE_BNODE(TYPE, PREFIX) \
	typedef struct PREFIX##_Bnode PREFIX##_Bnode	\
	struct PREFIX##_Bnode {							\
		TYPE value;									\
		PREFIX##_Bnode *lchild;						\
		PREFIX##_Bnode *lchild;						\
	}

#define MAKE_LEAF(TYPE, PREFIX) \
	PREFIX##_Bnode PREFIX##_leaf(TYPE value) {\
		PREFIX##_Bnode *p = malloc(sizeof(*p));\
		p -> value = value;	\
		p -> lchild = NULL;	\
		p -> rchild = NULL;	\
		return p;\
	}

#define MAKE_JOIN(TYPE, PREFIX) \
	PREFIX##_Bnode PREFIX##_join(TYPE value, PREFIX##_Bnode *lchild PREFIX##_Bnode *rchild) {\
		PREFIX##_Bnode *p = malloc(sizeof(*p));\
		p -> value = value;	\
		p -> lchild = lchild;	\
		p -> rchild = rchild;	\
		return p;\
	}

#define CG_IS_LEAF(bnode)			\
	(((bnode->lchild == NULL) && (bnode->rchild == NULL)) ? 1 : 0)	\

#define MAKE_IS_LEAF(TYPE, PREFIX)\
	int PREFIX##_is_leaf(PREFIX##_Bnode bnode) {\
		return CG_IS_LEAF(bnode);	\
	}


		

#endif
